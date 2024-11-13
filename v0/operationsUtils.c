#include "operationsUtils.h"



int list(Jeu jeux[] , int jeuxSize){
    for(int i = 0 ; i < jeuxSize ; i++){
        printf("%s \n", jeux[i].NomJeu  );
    }   
    return count(jeux) ;
}

