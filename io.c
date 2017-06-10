#include "io.h"

void game(){
  int  * board = generate();
  char   c1[2];
  char   c2[2];
  int    error;
  int    quit = 0;

  if(board){
    /*
     * TODO : affichage des regles
     */
    
    while(!quit && !lost(board) && !win(board)){
      putchar('\n');
      display_board(board);

      printf("    Veuillez saisir le caractere de la colonne puis celui de la ligne\ndes deux cases de votre choix s'il vous plait.\nExemple : AA\n          AB\nEntrez 00 pour quitter\n");
      error = saisies_choix(c1,c2);
      if((c1[0]=='0' && c1[1]=='0') || (c2[0]=='0' && c2[1]=='0')){
	quit = 1;
      }else if(error){
	puts("Saisie invalide.");
      }else{
	if(modify(board,c1[0]-'A',c1[1]-'A',c2[0]-'A',c2[1]-'A')){
	  puts("Ce choix n'est pas valide.");
	}
      }
    }

    if(!quit){
      if(win(board)){
	puts("You won !");
      }else{
	puts("You lose ...");
      }
    }
    free(board);
  }else{
    puts("Erreur d'initialisation de la grille. Pas assez de memoire.");
  }
}



void display_board(int * board){
  int i;
  int j;
  
  if(board){
    for(j=0;j<WIDTH;j++){
      putchar('A'+j);
      putchar(' ');
    }
    putchar('\n');
    for(j = 0; j < HEIGHT; j++){
      for(i = 0; i < WIDTH; i++){
	if(board[j*WIDTH+i]){
	  putchar(board[j*WIDTH+i]+'0');
	}else{
	  putchar(' ');
	}
	putchar(' ');
      }
      putchar('A'+j);
      putchar('\n');
    }
  }
}



int saisies_choix(char s1[2], char s2[2]){
  int error = 1;

  saisie(s1);
  if(valide_coord(s1[0]-'A',s1[1]-'A')){
    saisie(s2);
    error = !valide_coord(s2[0]-'A',s2[1]-'A');
  }

  return error;
}



void saisie(char s[2]){
  char c = 0;
  int  i = 0;

  while(c!='\n' && i<2){
    c=getchar();
    s[i++]=majuscule(c);
  }
  if(i<2){
    s[1]=0;
  }
  if(c!='\n' && (c=getchar())!='\n'){
    puts("Partie de la saisie ignoree :");
    c=getchar();
    while(c!='\n'){
      putchar(c);
      c=getchar();
    }
    putchar('\n');
    putchar('\n');
  }
}
