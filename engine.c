#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

/* Charge le plateau de jeu. Prend un nom de fichier en parametre, retourne un 
  pointeur sur une structure level definie dans engine.h
*/
level_t *loadLevel(char *filename) {
  level_t *m;
  m = malloc(sizeof(level_t));	//Allocation
  m->player = malloc(sizeof(mario_t));
  
  m->player[0].mario_w=SIZE2;
  m->player[0].mario_h=SIZE;
  m->player[0].mario_dx=MARIO_DX;
  m->player[0].mario_dy=MARIO_DY;

  int w, h, view;
  m->pos = 0;
  //Ouverture, affichage et fermeture du fichier
  
  FILE* f = fopen(filename, "r");
  char buffer[1024];
   
  if (f != NULL)
  {
	  fscanf(f, "%d %d %d", &h, &w, &view);
	  
		m->w = w;
		m->h = h;
		m->view = view;
		
//Allocation du tableau vide de taille h*w	  
	  m->t =  (char *)calloc(sizeof(char),m->w*m->h);
	  int i,j;
	  
//On remplit le tableau avec les éléments du niveau	  	  
	  for (i = 0; i < m->h; i++)
	  { 
		  memset(buffer,0,1024);
		  fgets(buffer,1024,f);
		  for (j = 0; j < m->w; j++)
		  {
			switch(buffer[j]) {
			  case '~': m->t[m->w*i+j]= WATER; break;
			  case '#': m->t[m->w*i+j]= GROUND; break;
			  case '-': m->t[m->w*i+j]= GRASS; break;
			  case '(': m->t[m->w*i+j]= BEGINGRASS; break;
			  case ')': m->t[m->w*i+j]= ENDGRASS; break;
			  case 'u': m->t[m->w*i+j]= UPGRASS1; break;
			  case '/': m->t[m->w*i+j]= UPGRASS2; break;
			  case '\\':m->t[m->w*i+j]= DOWNGRASS1; break;
			  case 'd': m->t[m->w*i+j]= DOWNGRASS2; break;
			  case 'x': m->t[m->w*i+j]= BRICK; break;
			  case '?': m->t[m->w*i+j]= BONUS2; break;
			  case '!': m->t[m->w*i+j]=BONUS1; break;
			  case 'O': m->t[m->w*i+j]=DOOR; break;
			  case '@': m->player[0].mario_x=j; m->player[0].mario_y=i; break;
			  //~ case 'a': m->monsterA[m->nma].x=i; m->monsterA[m->nma].y=j; m->monsterA[m->nma++].alive=1; break;
			  //~ case 'b': m->monsterB[m->nmb].x=i; m->monsterB[m->nmb].y=j; m->monsterB[m->nmb++].alive=1; break;
			  //~ case 'c': m->monsterC[m->nmc].x=i; m->monsterC[m->nmc].y=j; m->monsterC[m->nmc++].alive=1; break;
			  default: m->t[m->w*i+j]= EMPTY;
			}
			
		  }	  
		  
	  }
  m->player[0].mario_xpix = m->player[0].mario_x*m->player[0].mario_h;
  m->player[0].mario_ypix = m->player[0].mario_y*m->player[0].mario_w+208;
  
//Affichage dans le terminal avec des chiffres	  
	  for (i = 0; i < h; i++)
	  {
		  for (j = 0; j < w; j++)
		  {
			  printf("%d ", m->t[m->w*i+j]);
		  }
		  printf("\n");
	  }
	  
	  
	  fclose(f);
  }
 
  return m;
}
/* 
 * Mise a jour du plateau: deplace les personnages
*/
void update(level_t *m) {
	//~ if (event.type==SDL_KEYDOWN) {
		  //~ switch (event.key.keysym.sym) {
			  //~ case SDLK_RIGHT : 
				//~ m->player[0].x_pix += m->player[0].dx;
				//~ break;
			  //~ case SDLK_LEFT :
				//~ m->player[0].x_pix -= m->player[0].dx;
				//~ break;
			  //~ case SDLK_ESCAPE :
				//~ return 1;
		  //~ default: ;
		  //~ }
		//~ } 
	//~ else if (event.type==SDL_KEYUP) {
		//~ }
}
