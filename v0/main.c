#include <stdio.h>
#include "structures.h"
#include "operation.h"
#include <string.h>


int main() {
    printf("coucou\n");
    DemandeOperation dlOp;
    dlOp.CodeOp = 3;
    strcpy(dlOp.NomJeu, "GancarskiSimulator3000");
    strcpy(dlOp.Param, "https://test.fr/");
    execute_demande(dlOp);

    DemandeOperation listOp;
    listOp.CodeOp = 2;
    execute_demande(listOp);

    DemandeOperation existsOp;
    existsOp.CodeOp = 1;
    strcpy(existsOp.NomJeu, "GancarskiSimulator3000");
    printf("exists ? %d\n", execute_demande(existsOp));

    DemandeOperation deleteOp;
    deleteOp.CodeOp = 4;
    strcpy(deleteOp.NomJeu, "GancarskiSimulator3000");
    printf("delete success ? %d\n", execute_demande(deleteOp));

    DemandeOperation existsOp2;
    existsOp2.CodeOp = 1;
    strcpy(existsOp2.NomJeu, "GancarskiSimulator3000");
    printf("exists ? %d\n", execute_demande(existsOp2));

}
