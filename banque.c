#include "banque.h"

Para *creerPara(int duree, int tempsMoyenArrivee,
                int tempsServiceMin, int tempsServiceMax)
{
    Para *para = malloc(sizeof(Para));
    para->duree = duree;
    para->tempsMoyenArrivee = tempsMoyenArrivee;
    para->tempsServiceMin = tempsServiceMin;
    para->tempsServiceMax = tempsServiceMax;
    return para;
}

Stat *creerStat()
{
    Stat *stat = malloc(sizeof(Stat));
    stat->nbClient = 0;
    stat->tempsTotalService = 0;
    stat->tempsMoyenService = 0.0;
    return stat;
}

Banque *creerBanque(Para *para)
{
    Banque *banque = malloc(sizeof(Banque));

    banque->para = para;

    int index;
    for (index = 0; index < NB_CAISSIER; index++)
    {
        (banque->caissiers)[index] = creerCaissier(index + 1);
    }

    FileAttente *fileAttente = creerFileAttente();
    banque->file = fileAttente;

    banque->stat = creerStat();

    prepareLog(banque);

    return banque;

}

void prepareLog(Banque *banque)
{
    FILE *fichier = NULL;
    fichier = fopen("log.txt", "w");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ecriture dans le log");
        exit(EXIT_FAILURE);
    } else
    {
        banque->fichier = fichier;
    }
}

void simuler(Banque *banque)
{
    FILE *fichier = banque->fichier;
    setRandomSeed();
    printf("Environnement pret a servir les clients \n");

    int tempsSysteme;
    for (tempsSysteme = 0; (!finService(banque)) || (tempsSysteme <= banque->para->duree); tempsSysteme++)
    {

        fprintf(fichier, "######### Simulation Banque Tour %d ##################### \n", tempsSysteme);
        printf("######### Simulation Banque Tour %d ##################### \n", tempsSysteme);

        afficherFile(banque->file, banque->fichier);
        afficherTousCaissier(banque);

        int indexC;
        for (indexC = 0; indexC < NB_CAISSIER; indexC++)
        {
            Caissier *c = (banque->caissiers)[indexC];
            if (!estLibre(c))
            {
                fprintf(fichier, "Caissier No.%d continue a servir Client No.%d \n", indexC+1, c->clientServi->numero);
                c->tempsRestantService--;

                if (c->tempsRestantService == 0)
                {
                    fprintf(fichier, "Caissier No.%d a fini de servir Client No.%d \n", indexC+1, c->clientServi->numero);
                    banque->stat->tempsTotalService += tempsSysteme - c->clientServi->tempsArrivee;
                    c->clientServi->tempsDepart = tempsSysteme;
                    c->clientServi = NULL;

                    if (!estVide(banque->file))
                    {
                        Client *client = defiler(banque->file);
                        fprintf(fichier, "Client No.%d est defile pour etre servi par Caissier No.%d \n", client->numero, indexC++);
                        int randTempsService = randomInt(banque->para->tempsServiceMin, banque->para->tempsServiceMax);
                        servir(c, client, randTempsService);
                    }
                }
            }
            else
            {
                fprintf(fichier, "Caissier No.%d libre \n", indexC+1);
            }
        }

        if ((tempsSysteme <= banque->para->duree) && (tempsSysteme % banque->para->tempsMoyenArrivee == 0))
        {

            banque->stat->nbClient++;
            Client *client = creerClient(banque->stat->nbClient, tempsSysteme);

            printf("Client No.%d arrive. \n", client->numero);
            fprintf(fichier, "Client No.%d arrive. \n", client->numero);

            Caissier *c = getCaissierLibre(banque);
            if (c == NULL)
            {
                fprintf(fichier, "Client No.%d est enfile. \n", client->numero);
                enfiler(banque->file, client);
            }
            else
            {
                int randTempsService = randomInt(banque->para->tempsServiceMin, banque->para->tempsServiceMax);
                servir(c, client, randTempsService);
                printf("Caissier %d commence a servir Client NO.%d \n", c->numero, c->clientServi->numero);
                fprintf(fichier, "Caissier %d commence a servir Client NO.%d \n", c->numero, c->clientServi->numero);
            }
        }

        printf("####################################################################\n");
        fprintf(fichier, "####################################################################\n");
    }

    fclose(fichier);

    printf("Il y a totalement %d clients servi.\n", banque->stat->nbClient);
    printf("Le temps total de service est %d.\n", banque->stat->tempsTotalService);
    banque->stat->tempsMoyenService = banque->stat->tempsTotalService / banque->stat->nbClient;
}

Caissier *getCaissierLibre(Banque *banque)
{
    int indexC;
    for (indexC = 0; indexC < NB_CAISSIER; indexC++)
    {
        Caissier *c = (banque->caissiers)[indexC];
        if (estLibre(c))
        {
            return c;
        }
    }
    return NULL;
}

int finService(Banque *banque)
{
    int tousCaissierLibre = TRUE;
    int indexC;
    for (indexC = 0; indexC < NB_CAISSIER; indexC++)
    {
        Caissier *c = (banque->caissiers)[indexC];
        if (!estLibre(c))
        {
            tousCaissierLibre = FALSE;
            break;
        }
    }
    return tousCaissierLibre && estVide(banque->file);
}

void afficherTousCaissier(Banque *banque)
{
    FILE *fichier = banque->fichier;

    printf("***** Etat des caissier : \n");
    fprintf(fichier, "***** Etat des caissier : \n");
    int indexC;
    for (indexC = 0; indexC < NB_CAISSIER; indexC++)
    {
        Caissier *c = (banque->caissiers)[indexC];
        printf("Caissier No.%d ", c->numero);
        fprintf(fichier, "Caissier No.%d ", c->numero);
        if (c->clientServi == NULL)
        {
            printf("-clientServi : NULL");
            fprintf(fichier, "-clientServi : NULL");
        }
        else
        {
            printf("-clientServi No. %d", c->clientServi->numero);
            fprintf(fichier, "-clientServi No. %d", c->clientServi->numero);
        }

        printf("-tempsRestantService : %d \n", c->tempsRestantService);
        fprintf(fichier, "-tempsRestantService : %d \n", c->tempsRestantService);
    }
}
