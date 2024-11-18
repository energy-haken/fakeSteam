#include "structures.h"

int count(Jeu jeux[]);
Jeu* getGameByName(Jeu jeux[], char nom[]);
int get_index(Jeu jeux[], int nb_jeux, char nom[]);

//1
int exists(Jeu jeux[], int nb_jeux, char nom[]);

//2
int list(Jeu jeux[], int nb_jeux);

//3
int download(Jeu jeux[], int * nb_jeux, char nom[], char url[]);

//4
int delete(Jeu jeux[], int * nb_jeux, char nom[]);

//5
void simulate(Jeu jeux[], char nom[]);

//5
void execute(Jeu jeux[], char nom[]);

