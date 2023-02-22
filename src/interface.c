#include "../inc/arbre_bk.h"
#define NB_MOTS 50

void affiche_texte_erreurs(char* text, ArbreBK a){
    char* mot;
    int couleur;
    int x, y;
    couleur = 1;

    x = 2;
    y = 3;

    mot = strtok(text, " ");

    init_pair(couleur, COLOR_RED, COLOR_RED); 
    while(mot != NULL){
        if(est_dans_ArbreBK(a, mot) == 0) // if(mot == estDansListeErreur)
            mvprintw_color(y ,x, mot, couleur);
        else
            mvprintw(y, x, "%s \n", mot);

        x += strlen(mot)+1;
        mot = strtok(NULL, " ");
        refresh();
    }
}


int main(int argc, char *argv[]){
    ArbreBK a = NULL;

    FILE *file_dico = fopen(argv[1], "r");
    char *mot = (char*) malloc(sizeof(char) * 255);
    
    while(fscanf(file_dico, "%s", mot) != EOF){
        inserer_dans_ArbreBK(&a, mot);
        mot = (char*) malloc(sizeof(char) * 255);
    }
    clear();

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    start_color();
    // noecho();

    char* text = (char*) malloc(sizeof(char) * 256 * NB_MOTS);

    /* Ecrit texte */
    mvgetstr(2, 2, text);

    char* text_copy = (char*) malloc(sizeof(char) * 256 * NB_MOTS);
    strcpy(text_copy, text);
    

    clear();
    Liste correction = NULL;

    while(1){
        /* Detecte erreurs */
        affiche_texte_erreurs(text, a);

        int nb_char;
        int touche;
        int souris_x, souris_y;
        MEVENT ev;
        noecho();

        /* Detecte mot clique */
        correction = NULL; // Initialiser correction à NULL

        touche = getch();
        if(touche == KEY_MOUSE && getmouse(&ev) == OK) {
            souris_x = ev.x;
            souris_y = ev.y;
            nb_char = (souris_y - 3) * COLS + souris_x - 3;
        }

        if( ('a' < text[nb_char] && text[nb_char] < 'z') ||
            ('A' < text[nb_char] && text[nb_char] < 'Z') ) {
            char* mot = (char*) malloc(sizeof(char)*256);
            possede_ponctuation(mot);
            maj_to_min(mot);
            detecte_mot(nb_char, text_copy, mot);
            char* text_copy = (char*) malloc(sizeof(char) * 256 * NB_MOTS);

            mvprintw(1, 2, "Voici votre mot : %s", mot);

            /* Proposition */
            int seuil = Levenshtein(mot, a->mot);

            rechercher_dans_ArbreBK(a, mot, &correction, &seuil);
            printw_liste(correction);
            liberer_Liste(&correction);
            correction = NULL;

            affiche_texte_erreurs(text_copy, a);

            free(mot); // libérer la mémoire allouée pour mot
            free(text_copy); // libérer la mémoire allouée pour mot
        }
        refresh();
    }


    free(mot);
    free(text);
    free(text_copy);

    refresh();
    getch();
    endwin();

    return 0;
}