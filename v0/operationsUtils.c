#include "operationsUtils.h"
#include <string.h>
#include <stdio.h>
#include<unistd.h>

int list(Jeu jeux[], int nb_jeux){
    for(int i = 0 ; i < nb_jeux ; i++){
        printf("%s \n", jeux[i].NomJeu  );
    }
    return nb_jeux;
}

int download(Jeu jeux[], int * nb_jeux, char nom[], char url[]) {
    Jeu new_game;
    strcpy(new_game.NomJeu, nom);
    jeux[*nb_jeux] = new_game;
    printf("Downloading %s from %s...\n", nom, url);
    sleep(10);
    return 1;
}