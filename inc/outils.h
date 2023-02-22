#ifndef __OUTIL__
#define __OUTIL__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ncurses.h>
#include <time.h>
#include <sys/time.h>

#include "liste.h"
#include "levenshtein.h"

void possede_ponctuation(char* mot);
void maj_to_min(char *mot);
float time_diff(struct timeval *start, struct timeval *end);

void mvprintw_color(int y, int x, char* str, int couleur);
void detecte_mot(int i, char* texte, char* mot);
void printw_liste(Liste lst);

#endif