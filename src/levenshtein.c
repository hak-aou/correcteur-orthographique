#include "../inc/levenshtein.h"

int min(int a, int b, int c){
    if (a <= b && a <= c)
        return a;
    if (b <= a && b <= c)
        return b;
    if (c <= b && c <= a)
        return c;
    return -1;
}

int Levenshtein(char * un, char * deux){
    int i, j, taille_un, taille_deux, coutSub, **D;
    taille_un = strlen(un);
    taille_deux = strlen(deux);
    D = (int**) malloc(sizeof(int*) * (taille_un + 1));

    for(i = 0 ; i < taille_un + 1 ; i++){
        D[i] = (int*) malloc(sizeof(int) * (taille_deux + 1));
        D[i][0] = i;
    }

    for(j = 0 ; j < taille_deux + 1 ; j++)
        D[0][j] = j;


    for(i = 1 ; i < taille_un + 1 ; i++)
        for(j = 1 ; j < taille_deux + 1 ; j++){
            if(un[i - 1] == deux[j - 1])
                coutSub = 0;
            else
                coutSub = 1;
            D[i][j] = min(D[i-1][j] + 1, D[i][j-1] + 1, D[i-1][j-1] + coutSub);
        }
        
    /* On stocke la distance de Levenshtein */ 
    int d = D[taille_un][taille_deux];

    /* On libère le tableau à deux dimension */
    for(i = 0 ; i < taille_un + 1 ; i++){
        free(D[i]);
    }
    free(D);
    
    return d;
}