#ifndef _MINIJEU_IO_KLEVH_
#define _MINIJEU_IO_KLEVH_

#include <stdio.h>
#include "jeu.h"

#define majuscule(c) (c>='a' && c<='z'?c-'a'+'A':c)

void game();

void display_board(int * board);

int saisies_choix(char s1[2], char s2[2]);

void saisie(char s[2]);

#endif
