#include "operationsUtils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <CodeOp> <NomJeu> <Param>\n", argv[0]);
        return 1;
    }
    Jeu jeux[20]; 
    int nb_jeux = 0; 
    download(jeux, &nb_jeux, argv[1], argv[2]);
    return 0;
}
