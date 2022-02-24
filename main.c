#include "utils.h"
#include "file.h"
#include "banque.h"

int main(void)
{
    int duree=100, tempsMoyenArrivee=10, tempsServiceMin=10, tempsServiceMax=30;

    printf("########### Simulation de banque ################\n");
    printf("Saisir respectivement les Parametres de la simulation en les separant avec espace : \n");
    printf("-- Duree de la simulation\n");
    printf("-- Temps moyen d'arrrivees entre les clients\n");
    printf("-- Temps minimal du service d'un cassier pour un client\n");
    printf("-- Temps maximal du service d'un cassier pour un client\n");
    scanf("%d %d %d %d", &duree, &tempsMoyenArrivee, &tempsServiceMin, &tempsServiceMax);

    Para *para = creerPara(duree, tempsMoyenArrivee, tempsServiceMin, tempsServiceMax);
    printf("Duree de la simulation : %d \n", para->duree);
    printf("Temps moyen d'arrrivees entre les clients : %d \n", para->tempsMoyenArrivee);
    printf("Temps minimal du service d'un cassier pour un client : %d \n", para->tempsServiceMin);
    printf("Temps maximal du service d'un cassier pour un client : %d \n", para->tempsServiceMax);

    printf("Faites ENTREZ pour demarrer la simulation : \n");
    fflush(stdin);
    getchar();

    Banque * banque = creerBanque(para);
    printf("Banque creee, demarrage de la simulation \n");

    simuler(banque);

    printf("Le temps moyen de service par client est %f\n", banque->stat->tempsMoyenService);
    printf("########### Fin de simulation ################\n");

    return 0;
}

