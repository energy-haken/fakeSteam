#include "operation.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Jeu *jeux = NULL;
int nb_jeux = 0;
int execute_demande(DemandeOperation op) {
    if (jeux == NULL){
        jeux = malloc(20 * sizeof(Jeu));
        memset(jeux, 0, 20* sizeof(Jeu));
    }
    switch (op.CodeOp) {
        case 1: 
            return exists(jeux, nb_jeux, op.NomJeu);
        case 2:
            return list(jeux, nb_jeux);
        case 3:
            return download(jeux, &nb_jeux, op.NomJeu, op.Param);
        case 4:
            return delete(jeux, &nb_jeux, op.NomJeu);
        case 5:
            simulate(jeux, nb_jeux, op.NomJeu);
            return 0;
        case 6:
            execute(jeux, nb_jeux, op.NomJeu);
            return 0;
    }
    return -5;
}
