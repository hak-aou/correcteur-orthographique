#ifndef __BK__
#define __BK__

#include "outils.h"

typedef struct noeudBK{
    char *mot;
    int valeur;
    struct noeudBK *filsG;
    struct noeudBK *frereD;
}NoeudBK, *ArbreBK;

int inserer_dans_ArbreBK(ArbreBK *A, char *mot);
int est_dans_ArbreBK(ArbreBK A, char *mot);
void liberer_ArbreBK(ArbreBK *A);
void affiche_ArbreBK(ArbreBK A);
Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot, Liste *correction, int *seuil);

#endif