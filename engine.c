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
  
  int w, h, view;
  m->pos=0;
  //Ouverture, affichage et fermeture du fichier
  
  FILE* f = fopen(filename, "r"); 
  if (f != NULL)
  {
	  fscanf(f, "%d %d %d", &h, &w, &view);
	  
		m->w = w;
		m->h = h;
		m->view = view;
		
//Allocation du tableau vide de taille h*w	  
	  m->t = malloc(sizeof(int*)*h);
	  int i,j;
	  for (i = 0; i < h; i++)
	  {
		  m->t[i] = malloc(sizeof(int*)*w);
	  }
	  
//On remplit le tableau avec les éléments du niveau	  	  
	  for (i = 0; i < h; i++)
	  { 
		  for (j = 0; j < w; j++)
		  {
			char c;
			fscanf(f, "%c", &c);
			switch (c)
			{
			  case '#': 
				  m->t [i][j]=GROUND;
				  break;
			  case '(': 
				  m->t [i][j]=BEGINGRASS;
				  break;
			  case ')': 
				  m->t [i][j]=ENDGRASS;
				  break;
			  case '/': 
				  m->t [i][j]=UPGRASS2;
				  break;
			  case '\\': 
				  m->t [i][j]=DOWNGRASS1;
				  break;
			  case 'u': 
				  m->t [i][j]=UPGRASS1;
				  break;
			  case 'd': 
				  m->t [i][j]=DOWNGRASS2;
				  break;
			  case 'x': 
				  m->t [i][j]=BRICK;
				  break;
			  case '+': 
				  m->t [i][j]=BONUS;
				  break;
			  case ' ': 
				  m->t [i][j]=EMPTY;
				  break;	
			  case '~': 
				  m->t [i][j]=WATER;
				  break;	  
			  case '-': 
				  m->t [i][j]=GRASS;
				  break;
			  default:
				  break;
			}
		  }	  
	  }

//Affichage dans le terminal avec des chiffres	  
	  for (i = 0; i < h; i++)
	  {
		  for (j = 0; j < w; j++)
		  {
			  printf("%d", m->t [i][j]);
		  }
		  printf("\n");
	  }
	  
	  
	  fclose(f);
  }
 
  return m;
}
/* Mise a jour du plateau: deplace les personnages
*/
void update(level_t *m) {

}
