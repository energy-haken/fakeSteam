#include "structures.h";


Jeu* getGameByName(Jeu jeux[], char nom[]);

//1
int exists(Jeu jeux[], char nom[] , int jeuxSize);

//2
int list(Jeu jeux[]) , int jeuxSize;

//3
int download(Jeu jeux[], char nom[], char url[] , int jeuxSize);

//4
int remove(Jeu jeux[], char nom[] , int jeuxSize);

//5
void simulate(Jeu jeux[], char nom[]);

//5
void execute(Jeu jeux[], char nom[]);


