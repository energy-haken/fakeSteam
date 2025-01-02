#include "operationsUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <CodeOp> <NomJeu>\n", argv[0]);
        return 1;
    }
    Jeu jeux[20]; 
    int nb_jeux = 0; 
    int result = delete(jeux, &nb_jeux, argv[2]);
    return result;
}
