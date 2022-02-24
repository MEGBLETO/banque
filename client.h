#ifndef DEF_CLIENT
#define DEF_CLIENT

#include "utils.h"

typedef struct client
{
    int numero;
    int tempsArrivee;
    int tempsDepart;
} Client;

Client *creerClient(int numero, int tempsArrivee);

#endif

