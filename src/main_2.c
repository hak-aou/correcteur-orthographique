#include "../inc/atr.h"


int main(int argc, char const *argv[]){

    /* ALGO 1 */

    ATR a = NULL;
    Liste lst_erreur = NULL;

    FILE *file_texte = fopen(argv[1], "r");
    FILE *file_dico = fopen(argv[2], "r");
    char mot[255];
    
    while(fscanf(file_dico, "%s", mot) != EOF){
        inserer_dans_ATR(&a, mot);
    }
    char *mot_co = (char*) malloc(sizeof(char) * 255);
    while(fscanf(file_texte, "%s", mot_co) != EOF){
        possede_ponctuation(mot_co);
        maj_to_min(mot_co);

        if(est_dans_ATR(&a, mot_co) != 1){ /* si c'est égale à 0 ou 2 */
            if(est_dans_Liste(lst_erreur, mot_co) == 0){
                inserer_en_tete(&lst_erreur, mot_co);
            }
        }
        mot_co = (char*) malloc(sizeof(char) * 255);
    }
    fclose(file_texte);

    /* ALGO 2 */

    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    
    Liste tmp = lst_erreur, correction = NULL;
    char *buffer;

    while(tmp != NULL){
        int dmin = INT_MAX;
        buffer = (char *) malloc(sizeof(char) * 256);
        creer_correction(a, buffer, tmp->mot, 0, &dmin, &correction);
        free(buffer);
        printf("\nMot mal orthographié : %s\nPropositions : ", tmp->mot);
        afficher_Liste(correction);
        liberer_Liste(&correction);
        
        tmp = tmp->suivant;
    }

    gettimeofday(&end, NULL);

    printf("\nAprès parcours d'un ATR dans le fichier '%s'\n", argv[2]);
    printf("Temps écoulé : %f\n", time_diff(&start, &end));

    return 0;
}