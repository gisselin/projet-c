#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "engine.h"
#include "graphics.h"
/* Taille d'une image */

SDL_Surface *screen=NULL;
/* Tableau des images */
SDL_Surface *sprite[NTILES];
SDL_Surface *marios[NB_MARIOS];
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
  case 0 : return BONUS1;
  case 5*13 : return BONUS2;
  case 1 : return DOOR;
  default: return -1;
  }
}
#define MARIO "data/marios.bmp"
void loadMario() {
  int i;
  /* Charge les sprites */
  SDL_Surface *tileset=SDL_LoadBMP(MARIO);
  if (tileset==NULL) fprintf(stderr,"file %s cannot be found\n",MARIO);
  for (i=0; i<NB_MARIOS; i++) {
    SDL_Rect srcRect,dstRect;
    marios[i] = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCCOLORKEY, SIZE2, SIZE, 32,0,0,0,0);
    srcRect.x = SIZE2*i;
    srcRect.y = 0;
    srcRect.w = SIZE2;
    srcRect.h = SIZE;
    dstRect.x = 0;
    dstRect.y = 0;
    SDL_BlitSurface(tileset, &srcRect, marios[i], &dstRect);
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
		  for (j = m->pos; j < (m->pos + m -> view) ; j++)
		  {
			  SDL_Rect rect1;
			  rect1.w = SIZE;
			  rect1.h = SIZE;
			  rect1.x = (j - m->pos) * SIZE;
			  rect1.y = i*SIZE;
			  //SDL_SetColorKey(sprite[m->t[m->w*i+j]],SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0,0,0));
			  SDL_BlitSurface(sprite[m->t[m->w*i+j]], NULL, screen, &rect1);
			  
		  }
	  }
	  
/*On fait le placement du mario*/
	SDL_Rect mario;
	mario.w = m->player[0].mario_w;
	mario.h = m->player[0].mario_h;
	mario.x = m->player[0].mario_xpix;
	mario.y = m->player[0].mario_ypix;
	SDL_BlitSurface(marios[1], NULL, screen, &mario);
	
	
	
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
		  //~ case SDLK_RIGHT : 
			//~ m->pos++;
			//~ break;
		  //~ case SDLK_LEFT :
			//~ if (m->pos > 1)
			//~ {
				//~ m->pos--;
			//~ }
			//~ break;
		  case SDLK_RIGHT : 
				
				if (m -> player[0].mario_xpix > m->view*SIZE*0.5 )
				{
					m->pos++;
				}
				else
				{
					m->player[0].mario_xpix += m->player[0].mario_dx;
				}
				m->player[0].mario_x = (int)((m->player[0].mario_xpix/SIZE))+m->pos;
				
				break;
		  case SDLK_LEFT :
				m->player[0].mario_xpix -= m->player[0].mario_dx;
				m->player[0].mario_x = (int)(m->player[0].mario_xpix/SIZE);
				break;
		  case SDLK_ESCAPE :
			return 1;
      default: ;
      }
    } else if (event.type==SDL_KEYUP) {
    }
    m->player[0].mario_y = (int)((m->player[0].mario_ypix/SIZE));
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
/*Il faut comparer le tableau qui contient les coordonnées de mario avec 
 * le tableau qui contient les coordonnées du décor et regarder ce qu'il 
 * y a dans la case sous mario pour voir si il tombe.
 * Il faut aussi dire qu'on ne peut déplacer mario que dans un rectangle EMPTY*/
