/** Ce ficher contient des fonctions facilitant certains traitements courants */
#include"utils.h"

/** Afficher un message d'erreur de choix */
void choiceError()
{
    printf("Choix invalide, veuillez choisir a nouveau.\n");
}

/** Configurer la seed pour la g�n�ration al�atoire des s�ries */
void setRandomSeed()
{
    srand(time(NULL));
}

/** G�n�rer un entier al�atoire entre min et max inclus */
int randomInt(int min, int max)
{
    return rand() % (max + 1 - min) + min;
}

/** Afficher un titre entour� des '-' */
void printTitle(char* title)
{
    printf("--------- %s ---------\n", title);
}

