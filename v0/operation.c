#include "operation.h"
#include "operationsUtils.h"
#include <stddef.h>
#include <stdlib.h>

Jeu *jeux = NULL;

int execute_demande(Jeu * jeux, DemandeOperation op) {
    if (jeux == NULL){
        jeux = malloc(20 * sizeof(Jeu));
        memset(jeux, 0, 20* sizeof(Jeu));
    }
    switch (op.CodeOp) {
        case 1: 
            return exists(jeux, op.NomJeu);
        case 2:
            return list(jeux);
        case 3:
            return download(jeux, op.NomJeu, op.Param);
        case 4:
            return remove(jeux, op.NomJeu);
        case 5:
            simulate(jeux, op.NomJeu);
            return 0;
        case 6:
            execute(jeux, op.NomJeu);
            return 0;
    }
}
