#include "operationsUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <CodeOp> <NomJeu> <Code>\n", argv[0]);
        return 1;
    }
    Jeu jeux[20]; 
    int nb_jeux = 0; 
    strcpy(jeux[0].Code, argv[3]); 
    int result = exists(jeux, nb_jeux, argv[1]);
    return result;
}
