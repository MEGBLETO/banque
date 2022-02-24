/** Ce ficher contient des fonctions facilitant certains traitements courants */
#include"utils.h"

/** Afficher un message d'erreur de choix */
void choiceError()
{
    printf("Choix invalide, veuillez choisir a nouveau.\n");
}

/** Configurer la seed pour la génération aléatoire des séries */
void setRandomSeed()
{
    srand(time(NULL));
}

/** Générer un entier aléatoire entre min et max inclus */
int randomInt(int min, int max)
{
    return rand() % (max + 1 - min) + min;
}

/** Afficher un titre entouré des '-' */
void printTitle(char* title)
{
    printf("--------- %s ---------\n", title);
}

