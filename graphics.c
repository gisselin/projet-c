#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "graphics.h"
/* Taille d'une image */
#define SIZE 70
/* Fenetre de jeu */
SDL_Surface *screen=NULL;
/* Tableau des images */
SDL_Surface *sprite[NTILES];
SDL_Surface *background;
/* Tableau des noms de fichier d'images. Correspond aux numeros des images
   dans engine.h
*/
#define TILESET "data/tileset.bmp"
int getsprite(n) {
  switch(n) {
  case 10*13+8: return BEGINGRASS;
  case 8*13+7: return GRASS;
  case 8*13+8: return ENDGRASS;
  case 12*13+8: return GROUND;
  case 8: return DOWNGRASS1;
  case 2*13+8: return UPGRASS2;
  case 12*13+7: return DOWNGRASS2;
  case 13+8: return UPGRASS1;
  case 3: return BRICK;
  case 8*13+6: return WATER;
  default: return -1;
  }
}
/* Charge les différentes images du jeu. A appeler une fois dans le main. */
void loadSprites() {
  int i,j;
  /* Charge les sprites */
  SDL_Surface *tileset=SDL_LoadBMP(TILESET);
  if (tileset==NULL) fprintf(stderr,"file %s cannot be found\n",TILESET);
  for (i=0; i<13; i++) {
    for (j=0; j<13; j++) {
      SDL_Rect srcRect,dstRect;
      int k=getsprite(i*13+j);
      if (k>=0) {
	sprite[k] = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCCOLORKEY, SIZE, SIZE, 32,0,0,0,0);
	srcRect.x = j*(SIZE+2);
	srcRect.y = i*(SIZE+2);
	srcRect.w = SIZE;
	srcRect.h = SIZE;
	dstRect.x = 0;
	dstRect.y = 0;
	SDL_BlitSurface(tileset, &srcRect, sprite[k], &dstRect);
      }
    }
  }
}


/* Affiche tout le plateau de jeu. A COMPLETER */

void paint(level_t *m) {
	
  /* Un rectangle a utiliser pour dire ou afficher l'image. */ 
  SDL_Rect rect;
  int i,j;
  /* La taille de l'image et sa position a afficher */
  rect.w = SIZE;
  rect.h = SIZE;
  rect.x = 0;
  rect.y = 0;
  
  /* Efface l'écran en le mettant tout noir */
  SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,60,120,250));
  
  /* Affiche les sprites du plateau de jeu */
  for (i = 0; i < m->h; i++)
	  {
		  for (j = 0; j < m->view; j++)
		  {
			  rect.x = j*SIZE;
			  rect.y = i*SIZE;
			  SDL_BlitSurface(sprite[m->t[i][j]], NULL, screen, &rect);
		  }
	  }


  /* Met a jour la fenetre */
  SDL_Flip(screen);
}

/* Capture les evenements clavier/fenetre */
/* Retourne 1 si il faut quitter le jeu, 0 sinon.*/
/* A REMPLIR */
int getEvent(level_t *m) {
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
  SDL_Event event;
  /* Ecoute les événements qui sont arrivés */
  while( SDL_PollEvent(&event) ){
    /* On a fermé la fenetre -> quitter le jeu */
    if (event.type==SDL_QUIT) return 1;
    /* On a appuyé sur une touche */
    if (event.type==SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
	/* Par exemple, les touches de direction du clavier. A remplir */
	/* A REMPLIR */
      default: ;
      }
    } else if (event.type==SDL_KEYUP) {
    }
  }
  return 0;
}

/* Ouvre une fenêtre avec de taille wxh tuiles de plateau de jeu. */ 
void initWindow(int w,int h) {
  if (SDL_Init(SDL_INIT_VIDEO)==-1) {
    fprintf(stderr,"error %s\n",SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);
  fprintf(stderr,"size %d %d\n",w*SIZE,h*SIZE);
  screen = SDL_SetVideoMode(w*SIZE,h*SIZE,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
  if (screen== NULL) {
    fprintf(stderr,"error video mode: %s\n", SDL_GetError()) ;
    exit(1);
  }
}
