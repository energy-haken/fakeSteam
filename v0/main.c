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
}
