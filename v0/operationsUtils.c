#include "operationsUtils.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int exists(Jeu jeux[], int nb_jeux, char nom[]){
    if (get_index(jeux, nb_jeux, nom) == -1) return 1;
    return 0;
}
int list(Jeu jeux[], int nb_jeux){
    printf("Listing available game:\n");
    for(int i = 0 ; i < nb_jeux ; i++){
        printf("%s (%lukB)\n", jeux[i].NomJeu, strlen(jeux[i].Code));
    }
    return nb_jeux;
}

int download(Jeu jeux[], int * nb_jeux, char nom[], char url[]) {
    Jeu new_game;
    int r = rand() % 1000;
    char code[1001];
    for (int i = 0; i < r; i++) {
        code[i] = '*';
    }
    code[r] = '\0';
    strcpy(new_game.NomJeu, nom);
    strcpy(new_game.Code, code);
    jeux[*nb_jeux] = new_game;
    printf("Downloading %s from %s...\n", nom, url);
    sleep(1);
    (*nb_jeux)++;
    return r;
}

int delete(Jeu jeux[], int * nb_jeux, char nom[]) {
    int idx = get_index(jeux, *nb_jeux, nom);
    if (idx == -1) {
        return -1;
    }
    int size = strlen(jeux[idx].Code);
    for (int i = idx; i < *nb_jeux - 1; i++) {
        jeux[i] = jeux[i + 1];
    }
    (*nb_jeux)--;
    return size;
}

int get_index(Jeu jeux[], int nb_jeux, char nom[]) {
    for(int i = 0 ; i < nb_jeux ; i++){
        if (strcmp(nom, jeux[i].NomJeu) == 0) return i;
    }
    return -1;
}