typedef struct
{
    int CodeOp;
    char NomJeu[25];
    char Param[200];
    int flag;
} DemandeOperation;

typedef struct {
    char NomJeu[25] ;
    char *code;
} Jeu;