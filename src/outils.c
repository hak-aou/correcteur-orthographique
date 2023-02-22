#include "../inc/outils.h"

/*
Paramètre : Un mot
Utilité : Retire les signes de ponctuation si il y en a dans un mot.
Retourne : Rien
*/
void possede_ponctuation(char* mot){
    do{
        if(*mot == '.' || *mot == ','){
            *mot = '\0';
        }
    } while(*mot++ != '\0');
}


/*
Paramètre : Un mot
Utilité : Transforme les majuscules en minuscule si il y en a dans un mot.
Retourne : Rien
*/
void maj_to_min(char *mot){
    do{
        if('A' <= *mot && *mot <= 'Z'){
            *mot = *mot + 32; // a-A = 32
        }
    } while(*mot++ != '\0');
}

/* Pour calculer le temps écoulé */

float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

/* Pour l'application */

void mvprintw_color(int y, int x, char* str, int couleur){
    attron(COLOR_PAIR(couleur));
    mvprintw(y, x, "%s", str);
    attroff(COLOR_PAIR(couleur));
}


void detecte_mot(int i, char* texte, char* mot){
    while(texte[i] != ' '){  
        --i;
        if(i==-1)
            break;   
    }

    ++i;

    int j;
    j = 0;
    while(texte[i] != ' '){     
        mot[j] = texte[i];
        ++i;   
        ++j;
    }
    mot[j] = '\0';
}

void printw_liste(Liste lst){
    if(lst == NULL)
        return;
    int x, y;
    x = 17;
    y = 0;
    
    /* Efface première ligne */
    move(0, 0);
    clrtoeol();

    mvprintw(0, 2, "Propositions : ");

    int max = 10;
    int i = 0;

    while (lst->suivant != NULL && i < max) {
        mvprintw(y, x, "%s, ", lst->mot);
        x += strlen(lst->mot) + 2;
        lst = lst->suivant;
        i++;
    }
}