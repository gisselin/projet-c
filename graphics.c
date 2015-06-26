#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "engine.h"
#include "graphics.h"

/* Taille d'une image */

SDL_Surface *screen=NULL;
SDL_Surface *score_affichage=NULL;
SDL_Surface *bonus_affichage=NULL;
//The music that will be played
Mix_Music *music = NULL;
//The sound effects that will be used
Mix_Chunk *tralala = NULL;
Mix_Chunk *dingdingdong = NULL;
//The color of the font
SDL_Color textColor = { 255, 255, 255 };
SDL_Color textBonusColor = { 0, 255, 0 };
TTF_Font *font = NULL;
/* Tableau des images */
SDL_Surface *sprite[NTILES];
SDL_Surface *marios[NB_MARIOS];
SDL_Surface *background;

int courir;
int monstre1;
int monstre2;

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
  case 13*13+8: return MONSTER_A;
  case 13*13 : return MONSTER_B;
  case 13*13+4: return MONSTER_C;
  default: return -1;
  }
}
#define MARIO "data/marios.bmp"
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

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
  for (i=0; i<14; i++) {
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
	//SDL_SetColorKey(sprite[k], SDL_SRCCOLORKEY, SDL_MapRGB(screen->format,0,0,0));
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
			  //SDL_SetColorKey(sprite[m->t[m->w*i+j]], SDL_SRCCOLORKEY, SDL_MapRGB(screen->format,0,0,0));
			  SDL_BlitSurface(sprite[m->t[m->w*i+j]], NULL, screen, &rect1);
			  
		  }
	  }
	  
	  
	if (courir<20){
		courir++;
	}
	else if (courir = 20){
		courir = 0;
	}
	  
/*On fait le placement du mario*/
	SDL_Rect mario;
	mario.w = m->player[0].mario_w;
	mario.h = m->player[0].mario_h;
	mario.x = SIZE*(m->player[0].mario_x-m->pos);
	mario.y = SIZE*m->player[0].mario_y;
	SDL_SetColorKey(marios[courir], SDL_SRCCOLORKEY, SDL_MapRGB(screen->format,0,0,0));
	SDL_BlitSurface(marios[courir], NULL, screen, &mario);
	
	//Render the text
	char score_string[1000];
	sprintf(score_string, "%d", m->score);
    score_affichage = TTF_RenderText_Solid( font, score_string, textColor );
	//Show the message on the screen
    apply_surface( 20, 20, score_affichage, screen,NULL );

    //Free the message
    SDL_FreeSurface( score_affichage );
    
    char bonus_string[1000];

	sprintf(bonus_string, "Bonus Kill : %d", m->player[0].nb_kill);
	
    bonus_affichage = TTF_RenderText_Solid( font, bonus_string, textBonusColor );
	//Show the message on the screen
    apply_surface( 20, 80, bonus_affichage, screen,NULL );

    //Free the message
    SDL_FreeSurface( bonus_affichage );
  /* Met a jour la fenetre */
  SDL_Flip(screen);
}
void playKillSound()
{
	//Play the medium hit effect
                    if( Mix_PlayChannel( -1, tralala, 0 ) == -1 )
                    {
                        return ;
                    }
}
void playBonusSound()
{
	//Play the medium hit effect
                    if( Mix_PlayChannel( -1, dingdingdong, 0 ) == -1 )
                    {
                        return ;
                    }
}
void toggleMusic()
{
//If there is no music playing
                    if( Mix_PlayingMusic() == 0 )
                    {
                        //Play the music
                        if( Mix_PlayMusic( music, -1 ) == -1 )
                        {
                            return;
                        }
                    }
                    //If music is being played
                    else
                    {
                        //If the music is paused
                        if( Mix_PausedMusic() == 1 )
                        {
                            //Resume the music
                            Mix_ResumeMusic();
                        }
                        //If the music is playing
                        else
                        {
                            //Pause the music
                            Mix_PauseMusic();
                        }
                    }
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
		  
		  case SDLK_RIGHT : 
				m->player[0].dir = RIGHT;
				break;
		  case SDLK_LEFT :
				m->player[0].dir = LEFT;
				break;
		  case SDLK_UP :
				if (m->player[0].mario_y>3
				&& m->t[m->w*(m->player[0].mario_y + 1)+m->player[0].mario_x] != EMPTY)
				{
					m->player[0].mario_y -= 4;
				}
				break;
		  case SDLK_SPACE :
				mario_KillMonstersBonus2(m);
				break;
		case SDLK_a :
                
                toggleMusic();
                break;

		  case SDLK_ESCAPE :
			return 1;
      default: ;
      }
    } 
    else if (event.type==SDL_KEYUP) {
		m->player[0].dir = NONE;
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
  //Initialize SDL_ttf
    TTF_Init();
    //Initialize SDL_mixer
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );



  atexit(SDL_Quit);
  atexit(TTF_Quit);
  fprintf(stderr,"size %d %d\n",w*SIZE,h*SIZE);
  //Load the music
   music = Mix_LoadMUS( "data/gunther.wav" );
   //Load the sound effects
    tralala = Mix_LoadWAV( "data/tralala.wav" );
   dingdingdong = Mix_LoadWAV( "data/dingdingdong.wav" );
  font = TTF_OpenFont( "data/impact.ttf", 64 );
  screen = SDL_SetVideoMode(w*SIZE,h*SIZE,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
  toggleMusic();
  if (screen== NULL) {
    fprintf(stderr,"error video mode: %s\n", SDL_GetError()) ;
    exit(1);
  }
}

