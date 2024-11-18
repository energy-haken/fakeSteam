#pragma once

typedef struct
{
    int CodeOp;
    char NomJeu[25];
    char Param[200];
    int Flag;
} DemandeOperation;

typedef struct {
    char NomJeu[25] ;
    char *Code;
} Jeu;