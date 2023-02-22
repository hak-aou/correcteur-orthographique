#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __LISTE__
#define __LISTE__

typedef struct cel{
    char *mot;
    struct cel *suivant;
}Cellule, *Liste;

Cellule *allouer_Cellule(char * mot);
int inserer_en_tete(Liste * L, char * mot);
void liberer_Liste(Liste *L);
void afficher_Liste(Liste lst);
int est_dans_Liste(Liste lst, char *mot);

#endif