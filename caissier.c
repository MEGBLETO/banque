#include "caissier.h"

Caissier *creerCaissier(int numero)
{
    Caissier *caissier = malloc(sizeof(Caissier));
    caissier->numero = numero;
    caissier->clientServi = NULL;
    caissier->tempsRestantService = 0;
    return caissier;
}

void servir(Caissier *caissier, Client *client, int tempsService)
{
    caissier->clientServi = client;
    caissier->tempsRestantService = tempsService;
}

int estLibre(Caissier *caissier)
{
    return caissier->clientServi == NULL;
}
