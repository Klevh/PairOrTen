#include "jeu.h"

int modify(int * board,int x1,int y1,int x2,int y2){
  int i;
  int error = 1;

  if((abs(x2-x1)+abs(y2-y1)/2<=1 || abs(y1*WIDTH+x1-y2*WIDTH-x2)<=1) && valide_coord(x1,y1) && valide_coord(x2,y2) && (board[y1*WIDTH+x1]==board[y2*WIDTH+x2] || board[y1*WIDTH+x1]+board[y2*WIDTH+x2]==10) && board[y1*WIDTH+x1] && board[y2*WIDTH+x2] && (x1!=x2 || y1!=y2)){
    error = 0;
    
    for(i=min(y1*WIDTH+x1,y2*WIDTH+x2);i<max(y1*WIDTH+x1,y2*WIDTH+x2)-1;++i){
      board[i]=board[i+1];
    }
    
    while(i<HEIGHT*WIDTH-2 && board[i]){
      board[i]=board[i+2];
      i++;
    }
    board[i]=0;
    board[i+1]=0;
  }
  
  return error;
}



int * generate(int * board){
  int i;

  if(!board){
    board=malloc(HEIGHT*WIDTH*sizeof(*board));
  }
  srand(time(0));

  for(i=0;i<HEIGHT*WIDTH;++i){
    board[i]=rand()%9+1;
  }
  
  return board;
}



int lost(int * board){
  int lost = 1;
  int i = 0;
  int j = 0;

  while(lost && i<HEIGHT*WIDTH-1 && board[i] && board[i+1]){
    lost = board[i]!=board[i+1] && board[i]+board[i+1]!=10;
    ++i;
  }

  if(lost){
    while(j<HEIGHT-1 && lost && board[j*WIDTH+i] && board[(j+1)*WIDTH+i]){
      i=0;
      while(i<WIDTH && lost && board[j*WIDTH+i] && board[(j+1)*WIDTH+i]){
	lost=board[j*WIDTH+i]!=board[(j+1)*WIDTH+i] && board[j*WIDTH+i]+board[(j+1)*WIDTH+i]!=10;
	i++;
      }
      j++;
    }
  }

  return lost;
}
