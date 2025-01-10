#include "operationsUtils.h"
#include "common.h"

bool exists(Jeu jeux[], int nb_jeux, char nom[]){
    return (get_index(jeux, nb_jeux, nom) != -1);
}
void list(Jeu jeux[], int nb_jeux, char* buffer){
    buffer[0] = 0;
    for(int i = 0 ; i < nb_jeux ; i++){
        char temp[2048];
        sprintf(temp, "%s (%lukB)\n", jeux[i].NomJeu, strlen(jeux[i].Code));
        strcat(buffer, temp);
    }
    buffer[strlen(buffer) - 1] = 0;
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
        int cm = strcmp(nom, jeux[i].NomJeu);
        if (cm == 0) return i;
    }
    return -1;
}