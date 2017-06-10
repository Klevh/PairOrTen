#ifndef _MINIJEU_JEU_KLEVH_
#define _MINIJEU_JEU_KLEVH_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 4

#define abs(a) (a<0?-a:a)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define valide_coord(x,y) (x>=0 && y>=0 && x<WIDTH && y<HEIGHT)
#define win(tab) (!tab[0])

int modify(int * board,int x1,int y1,int x2,int y2);

int * generate();

int lost(int * board);

#endif
