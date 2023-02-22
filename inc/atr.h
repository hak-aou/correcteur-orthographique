#ifndef __ATR__
#define __ATR__

#include "outils.h"

typedef struct atr{
    char lettre;
    struct atr *fg;
    struct atr *fm;
    struct atr *fd;
}Noeud, *ATR;

ATR cree_ATR_vide();
void liberer_ATR(ATR *a);
void inserer_dans_ATR(ATR *a, char *mot);
void inserer_ATR_dans_ATR(ATR *a, ATR b);
int nb_mot_restant(ATR *a);
void supprimer_dans_ATR(ATR *a, char *mot);
void afficher_ATR_annexe(ATR a, char *mot, int indice);
void afficher_ATR(ATR* a);
int est_dans_ATR(ATR *a, char *mot);

void creer_correction(ATR a, char *mot, char *mot_co, int indice, int* dmin, Liste *correction);

void ecrireDebut(FILE *f);
void ecrireArbre(FILE *f, ATR a);
void ecrireFin(FILE *f);
void dessine(FILE *out, ATR a);
void creePDF(char *dot , char *pdf , ATR a);

#endif