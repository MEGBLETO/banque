#ifndef DEF_FILE
#define DEF_FILE

#include "client.h"

typedef struct element
{
    Client *client;
    struct element *suivant;
} Element;

typedef struct fileAttente
{
    Element *tete;
    Element *fin;
    int taille;
} FileAttente;

FileAttente *creerFileAttente();

void enfiler(FileAttente *file, Client *client);

Client *defiler(FileAttente *file);

int estVide(FileAttente *file);

void afficherFile(FileAttente *file, FILE *fichier);

#endif
