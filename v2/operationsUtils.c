#include "operationsUtils.h"
#include "common.h"

int exists(Jeu jeux[], int nb_jeux, char nom[]){
    if (get_index(jeux, nb_jeux, nom) == -1) return 1;
    return 0;
}
int list(Jeu jeux[], int nb_jeux){
    sleep(1);
    printf("Listing available game:\n");
    for(int i = 0 ; i < nb_jeux ; i++){
        printf("%s (%lukB)\n", jeux[i].NomJeu, strlen(jeux[i].Code));
    }
    return nb_jeux;
}

int download(Jeu jeux[], int * nb_jeux, char nom[], char url[]) {
    Jeu new_game;
    unsigned int r;
    getrandom(&r, sizeof(r), GRND_NONBLOCK);
    r %= 1000;
    char code[1001];
    for (int i = 0; i < r; i++) {
        code[i] = '*';
    }
    code[r] = '\0';
    strcpy(new_game.NomJeu, nom);
    strcpy(new_game.Code, code);
    (*nb_jeux)++;
    jeux[*nb_jeux] = new_game;
    printf("Downloading %s from %s...\n", nom, url);
    sleep(10);
    
    printf("Downloading %s from %s...DONE\n", nom, url);
   
    return r;
}

int delete(Jeu jeux[], int * nb_jeux, char nom[]) {
    sleep(2);
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
void simulate(Jeu jeux[], int nb_jeux, char nom[]) {
    int idx = get_index(jeux, nb_jeux, nom);
    if (idx == -1) return;
    char *memory = malloc(strlen(jeux[idx].Code) + 1);
    strcpy(memory, jeux[idx].Code);
    sleep(20);
    if (rand() % 2 == 0) {
        printf("Le gagnant du Jeu %s est A.\n", nom);
    } else {
        printf("Le gagnant du Jeu %s est B.\n", nom);
    }
    free(memory);
}

void execute(Jeu jeux[], int nb_jeux, char nom[]) {
    int idx = get_index(jeux, nb_jeux, nom);
    if (idx == -1) return;
    char *memory = malloc(strlen(jeux[idx].Code) + 1);
    strcpy(memory, jeux[idx].Code);
    printf("En attente d'un evenement clavier");
    getchar();
    if (rand() % 2 == 0) {
        printf("Le gagnant du Jeu %s est Serveur.\n", nom);
    } else {
        printf("Le gagnant du Jeu %s est Joueur.\n", nom);
    }
    free(memory);
}

int get_index(Jeu jeux[], int nb_jeux, char nom[]) {
    for(int i = 0 ; i < nb_jeux ; i++){
        if (strcmp(nom, jeux[i].NomJeu) == 0) return i;
    }
    return -1;
}