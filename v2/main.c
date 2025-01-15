#include <stdio.h>
#include "structures.h"
#include "operation.h"
#include "common.h"

int main() {
    DemandeOperation dlOp;
    dlOp.CodeOp = 3;
    dlOp.Flag = 0;
    strcpy(dlOp.NomJeu, "GancarskiSimulator3000");
    strcpy(dlOp.Param, "https://test.fr/");
    execute_demande(dlOp);

    DemandeOperation dlOp2;
    dlOp2.CodeOp = 3;
    dlOp2.Flag = 0;
    strcpy(dlOp2.NomJeu, "WemmertSimulator3000");
    strcpy(dlOp2.Param, "https://test.fr/");
    execute_demande(dlOp2);

    DemandeOperation dlOp3;
    dlOp3.CodeOp = 3;
    dlOp3.Flag = 0;
    strcpy(dlOp3.NomJeu, "ZimmermanSimulator3000");
    strcpy(dlOp3.Param, "https://test.fr/");
    execute_demande(dlOp3);
    
    
    
    
    
    
    wait_for_pending_ops();

   
   

    printf("list \n");

    DemandeOperation listOp;
    listOp.CodeOp = 2;
    execute_demande(listOp);

    printf("execute Wemmert\n");
    DemandeOperation executeOp;
    executeOp.CodeOp = 6;
    strcpy(executeOp.NomJeu, "WemmertSimulator3000");
    execute_demande(executeOp);

    printf("exist \n");
    DemandeOperation existsOp;
    existsOp.CodeOp = 1;
    strcpy(existsOp.NomJeu, "GancarskiSimulator3000");
    printf("exists ? %d\n", execute_demande(existsOp));

    printf("simulate \n");
    DemandeOperation simualteOp;
    simualteOp.CodeOp = 5;
    strcpy(simualteOp.NomJeu, "GancarskiSimulator3000");
    execute_demande(simualteOp);

    

   /*
    printf("delete Ganzarski \n");
    DemandeOperation deleteOp;
    deleteOp.CodeOp = 4;
    strcpy(deleteOp.NomJeu, "GancarskiSimulator3000");
    printf("delete success ? %d\n", execute_demande(deleteOp));
    
    printf("exist \n");
    DemandeOperation existsOp2;
    existsOp2.CodeOp = 1;
    strcpy(existsOp2.NomJeu, "GancarskiSimulator3000");
    printf("exists ? %d\n", execute_demande(existsOp2)); 

    printf("list \n");
    DemandeOperation listOp2;
    listOp2.CodeOp = 2;
    execute_demande(listOp2);
    */
}
