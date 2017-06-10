#ifndef _PAIRORTEN_IO_KLEVH_
#define _PAIRORTEN_IO_KLEVH_

#include <string.h>

#include "SANDAL2/SANDAL2.h"
#include "jeu.h"

#define WIN_WIDTH 600
#define WIN_HEIGHT 600

typedef struct{
  int * board;
  int selected[2];
  ElementSDL2 * e_sel[2];
  int end;
}board_t;

typedef struct number_data{
  board_t * board;
  char c;
  int id;
}number_data;

void validate(ElementSDL2 * this,SDL_Keycode kc);

void update_figure(ElementSDL2 * this);

void onclick_figure(ElementSDL2 * this);

void game();

#endif
