#include "file.h"

FileAttente *creerFileAttente()
{
    FileAttente *file = malloc(sizeof(FileAttente));
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    file->tete = NULL;
    file->fin = file->tete;
    file->taille = 0;
    return file;
}

void enfiler(FileAttente *file, Client *client)
{
    Element *element = malloc(sizeof(Element));
    if (element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    element->client = client;
    element->suivant = NULL;

    /** Le cas où la file n'était pas vide */
    if (file->taille != 0)
    {
        file->fin->suivant = element;
    }

    file->fin = element;

    /** Le cas où la file était vide */
    if (file->taille == 0)
    {
        file->tete = element;
    }

    file->taille++;
}

Client *defiler(FileAttente *file)
{
    if (file->taille > 0)
    {
        Client *resultat;

        Element *element = file->tete;
        resultat = element->client;

        file->tete = file->tete->suivant;

        /** Le cas où la file n'avait qu'un seul élément */
        if (file->taille == 1)
        {
            file->fin = NULL;
        }
        file->taille--;

        return resultat;
    }
    else
    {
        puts("Erreur : La file d'attente est vide!");
        exit(EXIT_FAILURE);
    }
}

int estVide(FileAttente *file)
{
    return file->taille == 0;
}

void afficherFile(FileAttente *file, FILE *fichier)
{
    printf("***** Etat de la file d'attente : \n");
    fprintf(fichier, "***** Etat de la file d'attente : \n");
    Element *element = file->tete;
    while (element != NULL)
    {
        printf("Client No. %d", element->client->numero);
        fprintf(fichier, "Client No. %d", element->client->numero);
        printf(" --> ");
        fprintf(fichier, " --> ");
        element = element->suivant;
    }
    printf("\n");
    fprintf(fichier, "\n");
}

