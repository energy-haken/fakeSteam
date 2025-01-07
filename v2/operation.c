#include "operation.h"
#include "common.h"

Jeu *jeux = NULL;
int *nb_jeux = NULL;
int op_pipe[2];
bool op_pipe_init = false;

void handle_sigalarm(int sig) {
    int message[2];
    while(read(op_pipe[0], message, sizeof(message)) > 0) {
        printf("[Operation Manager] Fork #%d exited with code %d\n", message[0], message[1]);        
    }
}

int execute_demande(DemandeOperation op) {
    int shm_fd;
    if (jeux == NULL) {
        // Créer et ouvrir un segment de mémoire partagée pour 'jeux'
        shm_fd = shm_open("/jeux_shm", O_CREAT | O_RDWR, 0666);
        ftruncate(shm_fd, 20 * sizeof(Jeu));
        jeux = mmap(0, 20 * sizeof(Jeu), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        memset(jeux, 0, 20 * sizeof(Jeu));

        // Créer et ouvrir un segment de mémoire partagée pour 'nb_jeux'
        shm_fd = shm_open("/nb_jeux_shm", O_CREAT | O_RDWR, 0666);
        ftruncate(shm_fd, sizeof(int));
        nb_jeux = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        *nb_jeux = 0;
    }
    if (!op_pipe_init) {
        pipe(op_pipe);
        fcntl(op_pipe[0], F_SETFL, O_NONBLOCK); 
        op_pipe_init = true;
        signal(SIGALRM, handle_sigalarm);
    }
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return -1; // Indiquer une erreur de fork
    }

    if (pid == 0) {
        // Processus enfant
        char *args[5];
        char code[1001];
        int idx = get_index(jeux, *nb_jeux, op.NomJeu);
        if (idx != -1) {
            strcpy(code, jeux[idx].Code);
        } else {
            strcpy(code, "");
        }
        args[0] = malloc(20);
        args[1] = malloc(25);
        args[2] = malloc(200);
        args[3] = malloc(1001);
        args[4] = NULL;
        sprintf(args[0], "%d", op.CodeOp);
        strcpy(args[1], op.NomJeu);
        strcpy(args[2], op.Param);
        strcpy(args[3], code);

        switch (op.CodeOp) {
            case 1: 
                execv("./bin/existsServ", args);
                break;
            case 2:
                execv("./bin/listServ", args);
                break;
            case 3:
                execv("./bin/downloadServ", args);
                break;
            case 4:
                execv("./bin/deleteServ", args);
                break;
            case 5:
                execv("./bin/simulateServ", args);
                break;
            case 6:
                execv("./bin/executeServ", args);
                break;
        }

        perror("execv failed");
        exit(1);
    } else {
        printf("[Operation Manager] Created fork #%d\n", pid);
        if (op.Flag == 0) return -2; // Opération non bloquante, on continue
        printf("[Operation Manager] Waiting for fork #%d to exit...\n", pid);
        int status;
        waitpid(pid, &status, 0); // Attendre que l'enfant se termine
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }
    
    return -5; // Valeur de retour par défaut, ne devrait jamais être atteint
}

void wait_for_pending_ops() {
    while(wait(NULL) > 0);
}