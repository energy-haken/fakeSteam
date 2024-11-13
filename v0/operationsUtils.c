#include "operationsUtils.h"


int count(Jeu jeux[]){
    int counter = 0 ;
    
    while(jeux[counter] != (Jeu)0 ){
        counter +=1 ;
        
    }
    return counter ;
    
}

int list(Jeu jeux[]){
    for(int i = 0 ; i < count(jeux) ; i++){
        printf("%s \n", jeux[i].NomJeu  );
    }
    return count(jeux) ;
}

