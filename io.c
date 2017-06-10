#include "io.h"

void validate(ElementSDL2 * this, SDL_Keycode kc){
  board_t * board;

  if(kc==13 && !getDataElementSDL2(this,(void**)&board)){
    if(board && board->selected[0]!=-1 && board->selected[1]!=-1){
      modify(board->board,board->selected[0]%WIDTH,board->selected[0]/WIDTH,board->selected[1]%WIDTH,board->selected[1]/WIDTH);
      onclick_figure(board->e_sel[0]);
      onclick_figure(board->e_sel[1]);
    }
  }
}



void update_figure(ElementSDL2 * this){
  number_data * info;
  char          s[2]=" ";

  if(this){
    getDataElementSDL2(this,(void**)&info);
    if(info){
      if(info->board->board[info->id]!=info->c-'0'){
	info->c=info->board->board[info->id]+'0';
	if(info->c-'0'){
	  s[0]=info->c;
	}
	setTextElementSDL2(this,s);
      }
    }
  }
}



void onclick_figure(ElementSDL2 * this){
  int           colors[2][4] = {{255,255,255,0},{140,140,140,0}};
  number_data * info;

  if(this){
    getDataElementSDL2(this,(void**)&info);
    if(info){
      if(info->board->selected[0]==info->id || info->board->selected[1]==info->id){
	setTextColorElementSDL2(this,colors[0]);
	if(info->board->selected[0]==info->id){
	  info->board->selected[0]=-1;
	  info->board->e_sel[0]=NULL;
	}else{
	  info->board->selected[1]=-1;
	  info->board->e_sel[1]=NULL;
	}
      }else if(info->board->selected[0]==-1 || info->board->selected[1]==-1){
	setTextColorElementSDL2(this,colors[1]);
	if(info->board->selected[0]==-1){
	  info->board->selected[0]=info->id;
	  info->board->e_sel[0]=this;
	}else{
	  info->board->selected[1]=info->id;
	  info->board->e_sel[1]=this;
	}
      }
    }
  }
}



void game(){
  /* Graphical display variables */
  ElementSDL2 * e;
  /* Game variables */
  board_t     * board; /* game's board */
  int           run; /* flag to end the game */
  int           tps, ticks, delay; /* settings variables for 60 frames/seconds */
  int           i,j; /* iterators */
  char          s[2]="0"; /* string for figures */
  number_data * figure_info; /* informations for figures */
  /* colors */
  int           noir[]={0,0,0,0};
  int           blanc[]={255,255,255,0};

  /* initialisation of game data */
  board = malloc(sizeof(*board));
  if(!board){
    puts("Error : not enough memory to run the game.");
    exit(-1);
  }
  board->board = generate(NULL);
  if(!board->board){
    puts("Error : not enough memory to run the game.");
    free(board);
    exit(-1);
  }
  board->selected[0] = -1;
  board->selected[1] = -1;
  board->e_sel[0]=NULL;
  board->e_sel[1]=NULL;

  /* SDL2 initialisation */
  if(initAllSDL2(IMG_INIT_JPG)){
    puts("Error : SDL2 could not be initialized");
    free(board->board);
    free(board);
    exit(-1);
  }

  /* opening of the window */
  if(initWindowSDL2(WIN_WIDTH,WIN_HEIGHT,"Pair Or Ten",0,noir,1)){
    free(board->board);
    free(board);
    closeAllSDL2();
    puts("Error : Opening the window failed");
    exit(-1);
  }

  /* ---- game phase initialisation ---- */
  /* element used to controle the physical board */
  e=createBlock(0,0,1,1,noir,1,32);
  if(!e){
    puts("Erreur : un element du jeu n'a pas put etre cree par manque de memoire.");
    free(board->board);
    free(board);
    closeAllWindowSDL2();
    closeAllSDL2();
    exit(-1);
  }
  setDataElementSDL2(e,board);
  setKeyPressElementSDL2(e,validate);
  
  /* graphical board generation */
  for(j=0;j<HEIGHT;j++){
    for(i=0;i<WIDTH;i++){
      s[0]=board->board[j*WIDTH+i]+'0';
      e=createTexte(1.f*WIN_WIDTH/(WIDTH+2)*(i+1),(.25f+j*.5f)*WIN_HEIGHT/HEIGHT,1.f*WIN_WIDTH/(WIDTH+2),.5f*WIN_HEIGHT/HEIGHT,"arial.ttf",s,blanc,SANDAL2_BLENDED,1,1);
      if(!e){
	puts("Erreur : un element du jeu n'a pas put etre cree par manque de memoire.");
	free(board->board);
	closeAllWindowSDL2();
	closeAllSDL2();
	exit(-1);
      }
      addHitBoxElementSDL2(e,rectangleHitBox(0,0,1,1),0);
      setActionElementSDL2(e,update_figure);
      setOnClickElementSDL2(e,onclick_figure);
      figure_info=malloc(sizeof(*figure_info));
      if(!figure_info){
	puts("Erreur : un element du jeu n'a pas put etre cree par manque de memoire.");
	free(board->board);
	closeAllWindowSDL2();
	closeAllSDL2();
	exit(-1);
      }
      figure_info->board=board;
      figure_info->id=j*WIDTH+i;
      figure_info->c=s[0];
      setDataElementSDL2(e,figure_info);
    }
  }

  /* boucle principale */
  run = 1;
  while(run>0){
    tps = SDL_GetTicks();
    run=!PollEventSDL2(NULL);
    if(lost(board->board)){
      run = -1;
    }else if(win(board->board)){
      run = -2;
    }

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

  if(run == -2){
    puts("You won !");
  }else if(run == -1){
    puts("You lose ...");
  }
  i=0;
  while(i<WIDTH*HEIGHT && board->board[i++]);
  printf("Your score is %d/%d\n",WIDTH*HEIGHT-i,WIDTH*HEIGHT);

  free(board->board);
  closeAllWindowSDL2();
  closeAllSDL2();
}
