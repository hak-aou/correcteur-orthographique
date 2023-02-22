#include "../inc/arbre_bk.h"

ArbreBK alloue_noeudBK(char *mot){
    ArbreBK A = (NoeudBK*) malloc(sizeof(NoeudBK));
    if(!A)
        return NULL;
    A->mot = malloc(sizeof(char) * 256);
    strcpy(A->mot, mot);
    A->valeur = 0;
    A->filsG = NULL;
    A->frereD = NULL;

    return A;
}

int inserer_dans_ArbreBK(ArbreBK *A, char *mot){
    static int D = 0;

    if(!*A){
        *A = alloue_noeudBK(mot);
        if(!*A)
            return 0;
        (*A)->valeur = D;
        return 1;
    }
    if(D != (*A)->valeur){
        inserer_dans_ArbreBK(&(*A)->frereD, mot);
    }
    else{
        D = Levenshtein((*A)->mot, mot);
        inserer_dans_ArbreBK(&(*A)->filsG, mot);
    }
    D = 0;
    return 1;
}

int est_dans_ArbreBK(ArbreBK A, char *mot){
    if(A){
        if(strcmp(A->mot, mot) == 0){
            return 1;
        }
        if(est_dans_ArbreBK(A->frereD, mot))
            return 1;
        if(est_dans_ArbreBK(A->filsG, mot))
            return 1;
    }
    return 0;
}

void liberer_ArbreBK(ArbreBK *A){
    if(!*A)
        return;
        
    if(!(*A)->filsG && !(*A)->frereD){
        free((*A)->mot);
        *A = NULL;
        free(*A);
    }
    else{
        liberer_ArbreBK(&(*A)->filsG);
        liberer_ArbreBK(&(*A)->frereD);
        *A = NULL;
        free(*A);
    }
}

void affiche_ArbreBK(ArbreBK A){
    if(A){
        printf("%s\n", A->mot);
        affiche_ArbreBK(A->frereD);
        affiche_ArbreBK(A->filsG);
    }
}

/* TROUVE DES PROPOSITIONS DE CORRECTION PAR PARCOURS DE L'A */

Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot, Liste *correction, int *seuil){
    if(!A)
        return NULL;
    int D = Levenshtein(A->mot, mot);
    
    if(D == *seuil)
        inserer_en_tete(correction, A->mot);
    else if(D < *seuil){
        liberer_Liste(correction);
        inserer_en_tete(correction, A->mot);
        *seuil = D;
    }

    ArbreBK tmp = A->filsG;
    while(tmp != NULL){
        if(abs(tmp->valeur - D) <= *seuil)
            rechercher_dans_ArbreBK(tmp, mot, correction, seuil);
        tmp = tmp->frereD;
    }
    return NULL;
}