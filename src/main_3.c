#include "../inc/arbre_bk.h"

int main(int argc, char const *argv[]){

    ArbreBK a = NULL;
    Liste lst_erreur = NULL;

    FILE *file_texte = fopen(argv[1], "r");
    FILE *file_dico = fopen(argv[2], "r");
    char *mot = (char*) malloc(sizeof(char) * 255);
    
    while(fscanf(file_dico, "%s", mot) != EOF){
        inserer_dans_ArbreBK(&a, mot);
        mot = (char*) malloc(sizeof(char) * 255);
    }

    char *mot_co = (char*) malloc(sizeof(char) * 255);
    while(fscanf(file_texte, "%s", mot_co) != EOF){
        
        possede_ponctuation(mot_co);
        maj_to_min(mot_co);

        if(est_dans_ArbreBK(a, mot_co) == 0){
            if(est_dans_Liste(lst_erreur, mot_co) == 0){
                inserer_en_tete(&lst_erreur, mot_co);
            }
        }
        mot_co = (char*) malloc(sizeof(char) * 255);
    }
    fclose(file_texte);

    /* RECHERCHE AVEC UN ARBRE BK */

    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);

    
    Liste tmp = lst_erreur, correction = NULL;

    while(tmp != NULL){
        int seuil = Levenshtein(tmp->mot, a->mot);
        rechercher_dans_ArbreBK(a, tmp->mot, &correction, &seuil);
        printf("\nMot mal orthographié : %s\n", tmp->mot);
        printf("Propositions : ");
        afficher_Liste(correction);
        liberer_Liste(&correction);
        tmp = tmp->suivant;
    }
    gettimeofday(&end, NULL);

    printf("\nAprès parcours d'un ArbreBK dans le fichier '%s'\n", argv[2]);
    printf("Temps écoulé : %f\n", time_diff(&start, &end));

    return 0;
}