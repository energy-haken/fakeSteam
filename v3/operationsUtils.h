#pragma once
#include "structures.h"
#include "stdbool.h"

int count(Jeu jeux[]);

int get_index(Jeu jeux[], int nb_jeux, char nom[]);

//1
bool exists(Jeu jeux[], int nb_jeux, char nom[]);

//2
void list(Jeu jeux[], int nb_jeux, char* buffer);

//4
int delete(Jeu jeux[], int * nb_jeux, char nom[]);
