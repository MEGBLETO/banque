#ifndef DEF_CAISSIER
#define DEF_CAISSIER

#include "client.h"

typedef struct caissier
{
    int numero;
    Client *clientServi;
    int tempsRestantService;
} Caissier;

Caissier *creerCaissier(int numero);

void servir(Caissier *caissier, Client *client, int tempsService);

int estLibre(Caissier *caissier);

#endif


