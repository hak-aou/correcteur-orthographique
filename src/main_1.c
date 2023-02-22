/* 
Ilhan ACHERCHOUR / Hakim AOUDIA
Algorithmique des arbres
S4-L2, 20/03/2022
*/
#include "../inc/atr.h"

int main(int argc, char const *argv[]){
    /* Affiche l'arbre lexicographique au format PDF */
    int affiche = 0;
    if(argc >= 4 && strcmp(argv[3], "-a") == 0){
        affiche = 1;
    }

    ATR a = NULL; /* Toujours initilaser l'arbre à NULL pour le bon fonctionnement des fonctions */
    Liste lst_erreur = NULL;

    FILE *file_texte = fopen(argv[1], "r");
    FILE *file_dico = fopen(argv[2], "r");
    char mot[255];

    /* On insère les mots du dictionnaire dans l'abre ternaire de recherche*/
    while(fscanf(file_dico, "%s", mot) != EOF){
        inserer_dans_ATR(&a, mot);
    }

    char *mot_co = (char*) malloc(sizeof(char) * 255);
    while(fscanf(file_texte, "%s", mot_co) != EOF){
        possede_ponctuation(mot_co);
        maj_to_min(mot_co);

        /* On teste si le mot du texte a corrige existe dans le dictionnaire*/
        if(est_dans_ATR(&a, mot_co) != 1){
            /* ON l'insère dans la liste chainee des erreurs sinon */
            inserer_en_tete(&lst_erreur, mot_co);
        }
        mot_co = (char*) malloc(sizeof(char) * 255);
    }
    printf("Mots mal orthographiés : ");
    afficher_Liste(lst_erreur);

    if(affiche == 1){
        creePDF("visualise.dot", "visualise.pdf", a);
        system("evince visualise.pdf");
    }

    return 0;
}