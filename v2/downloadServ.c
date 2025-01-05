#include "operationsUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <CodeOp> <NomJeu> <Param>\n", argv[0]);
        return 1;
    }
    // Ouvrir le segment de mémoire partagée pour 'jeux'
    int shm_fd = shm_open("/jeux_shm", O_RDWR, 0666);
    Jeu *jeux = mmap(0, 20 * sizeof(Jeu), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Ouvrir le segment de mémoire partagée pour 'nb_jeux'
    shm_fd = shm_open("/nb_jeux_shm", O_RDWR, 0666);
    int *nb_jeux = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    

    // Télécharger le jeu et mettre à jour 'nb_jeux'
    download(jeux, nb_jeux, argv[1], argv[2]);

    

    return 0;
}
