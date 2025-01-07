#include "operation.h"
#include "common.h"

Jeu *jeux = NULL;
int* nb_jeux = NULL;
int op_pipe[2] = {-1, -1};
bool op_pipe_init = false;

void handle_sigalarm(int sig) {
    int message[2];
    while(read(op_pipe[0], message, sizeof(message)) > 0) {
        printf("[Operation Manager] Fork #%d exited with code %d\n", message[0], message[1]);
    }
}

void init_global_vars() {
    if (jeux == NULL) {
        jeux = mmap(NULL, 20* sizeof(Jeu), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        memset(jeux, 0, 20 * sizeof(Jeu));
    }
    if (nb_jeux == NULL) {
        nb_jeux = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        *nb_jeux = 0;
    }
    if (op_pipe[0] == -1 && op_pipe[1] == -1) {
        pipe(op_pipe);
        fcntl(op_pipe[0], F_SETFL, O_NONBLOCK); 
        op_pipe_init = true;
        signal(SIGALRM, handle_sigalarm);
    }
}

int execute_demande(DemandeOperation op) {
    init_global_vars();

    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return -1; // Indiquer une erreur de fork
    }

    if (pid == 0) {
        // Processus enfant
        int result = -5;
        switch (op.CodeOp) {
            case 1: 
                result = exists(jeux, *nb_jeux, op.NomJeu);
                break;
            case 2:
                result = list(jeux, *nb_jeux);
                break;
            case 3:
                result = download(jeux, nb_jeux, op.NomJeu, op.Param);
                break;
            case 4:
                result = delete(jeux, nb_jeux, op.NomJeu);
                break;
            case 5:
                simulate(jeux, *nb_jeux, op.NomJeu);
                result = 0;
                break;
            case 6:
                execute(jeux, *nb_jeux, op.NomJeu);
                result = 0;
                break;
        }

        int message[2];
        message[0] = getpid();
        message[1] = result;
        write(op_pipe[1], message, sizeof(message));
        kill(getppid(), SIGALRM);
        exit(0);
    } else {
        printf("[Operation Manager] Created fork #%d\n", pid);
        if (op.Flag == 0) return -2; // Opération non bloquante, on continue
        printf("[Operation Manager] Waiting for fork #%d to exit...\n", pid);
        waitpid(pid, NULL, 0); // Attendre que l'enfant se termine
    }
    
    return -5; // Valeur de retour par défaut, ne devrait jamais être atteint
}

void wait_for_pending_ops() {
    while(wait(NULL) > 0);
}