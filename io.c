#include "io.h"

void game(){
  /* Graphical display variables */
  ElementSDL2 * e;
  /* Game variables */
  board_t       board; /* game's board */
  int           run; /* flag to end the game */
  int           tps, ticks, delay; /* settings variables for 60 frames/seconds */
  int           i,j; /* iterators */
  char          s[2]="0"; /* string for figures */
  /* colors */
  int           noir[]={0,0,0,0};
  int           blanc[]={255,255,255,0};

  /* initialisation of game data */
  board.board = generate(NULL);
  if(!board.board){
    puts("Error : not enough memory to run the game.");
    exit(-1);
  }
  board.hasChanged = 0;
  board.selected[0] = -1;
  board.selected[1] = -1; 

  /* SDL2 initialisation */
  if(initAllSDL2(IMG_INIT_JPG)){
    puts("Error : SDL2 could not be initialized");
    free(board.board);
    exit(-1);
  }

  /* opening of the window */
  if(initWindowSDL2(WIN_WIDTH,WIN_HEIGHT,"Pair Or Ten",0,noir,1)){
    free(board.board);
    closeAllSDL2();
    puts("Error : Opening the window failed");
    exit(-1);
  }

  /* ---- game phase initialisation ---- */
  /* generation de la grille */
  for(j=0;j<HEIGHT;j++){
    for(i=0;i<WIDTH;i++){
      s[0]=board.board[j*WIDTH+i]+'0';
      e=createTexte(1.f*WIN_WIDTH/(WIDTH+2)*(i+1),(.25f+j*.5f)*WIN_HEIGHT/HEIGHT,1.f*WIN_WIDTH/(WIDTH+2),.5f*WIN_HEIGHT/HEIGHT,"arial.ttf",s,blanc,SANDAL2_BLENDED,1,1);
      if(!e){
	puts("Erreur : un element du jeu n'a pas put etre cree par manque de memoire.");
	free(board.board);
	closeAllWindowSDL2();
	closeAllSDL2();
	exit(-1);
      }
    }
  }

  /* boucle principale */
  run = 1;
  while(run){
    tps = SDL_GetTicks();
    run=!PollEventSDL2(NULL);

    updateWindowSDL2();
    displayWindowSDL2();

    ticks = 16 - SDL_GetTicks() + tps - delay;
    if(ticks>0){
      SDL_Delay(ticks);
      delay=0;
    }else{
      delay=-ticks;
    }
  }

  free(board.board);
  closeAllWindowSDL2();
  closeAllSDL2();
}
