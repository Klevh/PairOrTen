#ifndef _PAIRORTEN_IO_KLEVH_
#define _PAIRORTEN_IO_KLEVH_

#include "SANDAL2/SANDAL2.h"
#include "jeu.h"

#define WIN_WIDTH 600
#define WIN_HEIGHT 600

typedef struct{
  int * board;
  int hasChanged;
  int selected[2];
}board_t;

typedef struct number_data{
  board_t * board;
  int id;
}number_data;

void game();

#endif
