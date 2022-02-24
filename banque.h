#ifndef DEF_BANQUE
#define DEF_BANQUE

#include "caissier.h"
#include "file.h"
#include "client.h"

#define NB_CAISSIER 3

typedef struct para
{
    int duree;
    int tempsMoyenArrivee;
    int tempsServiceMin;
    int tempsServiceMax;
} Para;

Para *creerPara(int duree, int tempsMoyenArrivee,
                int tempsServiceMin, int tempsServiceMax);

typedef struct stat
{
    int nbClient;
    int tempsTotalService;
    float tempsMoyenService;
} Stat;

Stat *creerStat();

typedef struct banque
{
    Para *para;
    Stat *stat;
    Caissier *caissiers[NB_CAISSIER];
    FileAttente *file;
    FILE *fichier;
} Banque;

Banque *creerBanque(Para *para);

void prepareLog(Banque *banque);

void simuler(Banque *banque);

Caissier *getCaissierLibre(Banque *banque);

int finService(Banque *banque);

void afficherTousCaissier(Banque *banque);

#endif
