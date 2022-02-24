#include "client.h"

Client *creerClient(int numero, int tempsArrivee)
{
    Client *client = malloc(sizeof(Client));
    client->numero = numero;
    client->tempsArrivee = tempsArrivee;
    return client;
}
