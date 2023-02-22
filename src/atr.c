/*
Ilhan ACHERCHOUR / Hakim AOUDIA
Algorithmique des arbres
S4-L2, 20/03/2022
*/
#include "../inc/atr.h"

/*
Paramètre : Rien
Utilité : Permet d'initialiser un arbre
Retourne : Retourne un arbre
*/
ATR cree_ATR_vide(){
    ATR arbre = (Noeud *) malloc(sizeof(Noeud));
    if(arbre == NULL){
        return NULL;
    }
    arbre->fg = NULL;
    arbre->fm = NULL;
    arbre->fd = NULL;
    return arbre;
}


/*
Paramètre : Arbre ternaire de recherche
Utilité : Permet de vider un ATR
Retourne : Rien
*/
void liberer_ATR(ATR *a){
    if(*a == NULL)
        return;
    else{
        liberer_ATR(&(*a)->fg);
        liberer_ATR(&(*a)->fm);
        liberer_ATR(&(*a)->fd);
        *a = NULL;
        free(*a);
    }
}


/*
Paramètre : Arbre ternaire de recherche et un mot
Utilité : Permet d'inserer dans un ATR un mot
Retourne : Rien
*/
void inserer_dans_ATR(ATR *a, char *mot){
    if(*a == NULL){
        *a = cree_ATR_vide();
        (*a)->lettre = *mot;
        if(*mot != '\0')
            inserer_dans_ATR(&(*a)->fm, mot + 1);
    }
    else if(*mot == '\0'){
        ATR ag = *a;
        ATR ad = (*a)->fd;
        *a = NULL;
        inserer_dans_ATR(a, mot);
        (*a)->fd = ag;
        (*a)->fd->fd = ad;
    }
    else if((*a)->lettre == *mot)
        inserer_dans_ATR(&(*a)->fm, mot + 1);
    else if((*a)->lettre > *mot)
        inserer_dans_ATR(&(*a)->fg, mot);
    else if((*a)->lettre < *mot)
        inserer_dans_ATR(&(*a)->fd, mot);
}


/*
Paramètre : Deux arbres ternaires de recherche
Utilité : Permet d'inserer un ATR dans un autre ATR
Retourne : Rien
*/
void inserer_ATR_dans_ATR(ATR *a, ATR b){
    if(b == NULL)
        return;
    if(*a == NULL)
        *a = b;
    else if((*a)->lettre > b->lettre)
        inserer_ATR_dans_ATR(&(*a)->fg, b);
    else if((*a)->lettre < b->lettre)
        inserer_ATR_dans_ATR(&(*a)->fd, b);
}


/*
Paramètre : Un arbre ternaire de recherche
Utilité : Permet de compter le nombre de '\0'
Retourne : Renvoie un int représentant le nombre de mots restant
*/
int nb_mot_restant(ATR *a){
    if(*a == NULL)
        return 0;
    if((*a)->lettre == '\0')
        return 1 + nb_mot_restant(&(*a)->fg) + nb_mot_restant(&(*a)->fd) + nb_mot_restant(&(*a)->fm);
    else
        return nb_mot_restant(&(*a)->fg) + nb_mot_restant(&(*a)->fd) + nb_mot_restant(&(*a)->fm);
}


/*
Paramètre : Un arbre ternaire de recherche et un mot
Utilité : Permet de supprimer un mot présent dans un ATR
Retourne : Rien
*/
void supprimer_dans_ATR(ATR *a, char *mot){
    int cpt = 0;
    int cas = 0;
    if(!a){
        fprintf(stderr, "mange\n");
        return;
    }
    if((*a)->lettre == *mot){
        cpt = nb_mot_restant(&(*a)->fm);
        cas = 1;
    }
    else if((*a)->fd && (*a)->fd->lettre == *mot){
        cpt = nb_mot_restant(&(*a)->fd->fm);
        cas = 2;
    }
    else if((*a)->fg && (*a)->fg->lettre == *mot){
        cpt = nb_mot_restant(&(*a)->fg->fm);
        cas = 3;
    }
    if(cpt <= 1 && cas != 0){
        if(cas == 1){
            ATR tmp = (*a);
            (*a) = NULL;
            free((*a));
            (*a) = tmp->fg;
            inserer_ATR_dans_ATR(a, tmp->fd);
        }
        else if(cas == 2){
            ATR tmp = (*a)->fd;
            (*a)->fd = NULL;
            free((*a)->fd);
            (*a)->fd = tmp->fg;
            inserer_ATR_dans_ATR(&(*a)->fd, tmp->fd);
        }
        else if(cas == 3){
            ATR tmp = (*a)->fg;
            (*a)->fg = NULL;
            free((*a)->fg);
            (*a)->fg = tmp->fg;
            inserer_ATR_dans_ATR(&(*a)->fg, tmp->fd);
        }
    }
    else if((*a)->lettre == *mot){
        supprimer_dans_ATR(&(*a)->fm, mot + 1);
    }
    else if((*a)->lettre < *mot){
        supprimer_dans_ATR(&(*a)->fd, mot);
    }
    else if((*a)->lettre > *mot){
        supprimer_dans_ATR(&(*a)->fg, mot);
    }
}


/*
Paramètre : Un arbre ternaire de recherche, un mot et un indice (int)
Utilité : Permet d'afficher les mots présents dans un ATR
Retourne : Rien
*/
void afficher_ATR_annexe(ATR a, char *mot, int indice){
    if(a){
        afficher_ATR_annexe(a->fg, mot, indice);

        mot[indice] = a->lettre;
        if(a->lettre == '\0'){
            printf("%s\n", mot);
        }
        afficher_ATR_annexe(a->fm, mot, indice + 1);
        afficher_ATR_annexe(a->fd, mot, indice);
    }
}

void afficher_ATR(ATR* a){
    char mot[255];
    afficher_ATR_annexe(*a, mot, 0);
}


/*
Paramètre : Un arbre ternaire de recherche et un mot
Utilité : Permet de savoir si un mot est présent dans un ATR
Retourne : 0 ou 2 si il n'existe pas dans l'ATR, 1 si il est présent l'ATR
*/
int est_dans_ATR(ATR *a, char *mot){
    if(*a == NULL)
        return 0;

    if((*a)->lettre == '\0' && *mot == '\0'){
        return 1;
    }

    if((*a)->lettre == *mot)
        return est_dans_ATR(&(*a)->fm, mot + 1);

    else if((*a)->lettre > *mot)
        return est_dans_ATR(&(*a)->fg, mot);

    else if((*a)->lettre < *mot)
        return est_dans_ATR(&(*a)->fd, mot);

    return 2;
}


/* TROUVE DES PROPOSITIONS DE CORRECTION PAR PARCOURS DE L'ATR */
void creer_correction(ATR a, char *mot, char *mot_co, int indice, int* dmin, Liste *correction){
    
    if(a){
        creer_correction(a->fg, mot, mot_co, indice, dmin, correction);
        
        mot[indice] = a->lettre;
        
        if(a->lettre == '\0'){
            int d = Levenshtein(mot_co, mot);
            if(d <= *dmin){
                if(d < *dmin){
                    *dmin = d;
                    liberer_Liste(correction);
                }
                inserer_en_tete(correction, mot);
            }
        }
        creer_correction(a->fm, mot, mot_co, indice + 1, dmin, correction);
        creer_correction(a->fd, mot, mot_co, indice, dmin, correction);
    }
}


/* PERMET DE VISUALISER LES ABRES TERNAIRES DE RECHERCHE */

void ecrireDebut(FILE *f){
	fprintf(f, "digraph arbre {\n");
	fprintf(f, "	node [shape = record, height = .1];\n");
	fprintf(f, "	edge [tailclip=false, arrowtail = dot, dir = both];\n");
}


void ecrireArbre(FILE *f, ATR a){
	if(a == NULL)
		return;
    char s[2];
    s[0] = a->lettre;
    s[1] = '\0';
	if(a->lettre != '\0'){
        fprintf(f,"	n%p [label=\"<gauche> | <valeur> %s | <droit>\"];\n", a, s);
    }
    else{
        fprintf(f,"	n%p [label=\"<gauche> | <valeur> 0 | <droit>\"];\n", a);
    }
	if(a->fg){
		fprintf(f, "	n%p : gauche : c -> n%p : valeur;\n", a, a->fg);
		ecrireArbre(f, a->fg);
	}
	if(a->fd){
		fprintf(f, "	n%p : droit : c -> n%p : valeur;\n", a, a->fd);
		ecrireArbre(f, a->fd);
	}
    if(a->fm){
		fprintf(f, "	n%p : valeur : c -> n%p : valeur;\n", a, a->fm);
		ecrireArbre(f, a->fm);
	}
}


void ecrireFin(FILE *f){
	fprintf(f, "}");
}


void dessine(FILE *out, ATR a){
	ecrireDebut(out);
	ecrireArbre(out, a);
	ecrireFin(out);
}


void creePDF(char *dot , char *pdf , ATR a) {
	FILE *out = fopen(dot , "w");
	dessine(out ,a);
	fclose(out);
	int len = strlen(dot) + strlen(pdf) + 15;
	char cmd[len];
	strcpy(cmd , "dot -Tpdf ");
	strcat(cmd , dot);
	strcat(cmd , " -o ");
	strcat(cmd , pdf);
	system(cmd);
}