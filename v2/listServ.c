#include "operationsUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <CodeOp>\n", argv[0]);
        return 1;
    }
    Jeu jeux[20]; 
    int nb_jeux = 0; 
    list(jeux, nb_jeux);
    return 0;
}
