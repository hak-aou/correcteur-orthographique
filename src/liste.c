/* 
Ilhan ACHERCHOUR / Hakim AOUDIA
Algorithmique des arbres
S4-L2, 20/03/2022
*/
#include "../inc/liste.h"


/*
Paramètre : Un mot
Utilité : Permet d'allouer une cellule dans la mémoire contenant un mot
et ayant comme suivant NULL
Retourne : Une cellule
*/
Cellule *allouer_Cellule(char * mot){
    Cellule *lst = (Cellule *) malloc(sizeof(Cellule));
    if(lst != NULL){
        lst->mot = (char *) malloc(sizeof(char) * 256);
        strcpy(lst->mot, mot);
        lst->suivant = NULL;
    }
    return lst;
}

/*
Paramètre : Une liste et un mot
Utilité : Permet d'inserer dans une liste chainée un mot en tete.
Retourne : Une cellule
*/
int inserer_en_tete(Liste * L, char * mot){
    Liste tmp = allouer_Cellule(mot);
    if(*L == NULL)
        *L = tmp;
    else if(tmp != NULL){
        tmp->suivant = *L;
        *L = tmp;
    }
    return 0;
}


/*
Paramètre : Une liste
Utilité : Permet de libérer une liste chainée
Retourne : Rien
*/
void liberer_Liste(Liste *L){
    Liste tmp;
    while(*L){
        tmp = *L;
        (*L) = (*L)->suivant;
        free(tmp->mot);
        free(tmp);
    }
}


/*
Paramètre : Une liste
Utilité : Permet de libérer une liste chainée
Retourne : Rien
*/
void afficher_Liste(Liste lst){
    if(lst != NULL)
    {
        if(lst->suivant == NULL)
            printf("%s", lst->mot);
        else
            printf("%s, ", lst->mot);
        afficher_Liste(lst->suivant);
    } else {
        printf("\n");
    }
}

int est_dans_Liste(Liste lst, char *mot){
    while(lst != NULL){
        if(strcmp(lst->mot, mot) == 0)
            return 1;
        lst = lst->suivant;
    }
    return 0;
}

