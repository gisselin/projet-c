#include <stdbool.h>
#define SIZE 70
#define SIZE2 44
#define NB_MARIOS 22
#define MARIO_DX 30
#define MARIO_DY SIZE
/* Fenetre de jeu */
/* Liste des tuiles du jeu, correspondant pour la plupart a des images */
enum {
  EMPTY=0,
  BEGINGRASS,
  ENDGRASS,
  GRASS,
  UPGRASS1,
  UPGRASS2,
  DOWNGRASS1,
  DOWNGRASS2,
  WATER,
  GROUND,
  BRICK,
  BONUS1,
  BONUS2,
  DOOR,
  NTILES
  
};

enum {
  NONE=0,
  LEFT,
  RIGHT
};




typedef struct {
	int mario_x,mario_y,mario_w,mario_h,mario_dx,mario_dy, mario_xpix, mario_ypix;
	bool alive;
} mario_t;

typedef struct {
  int w,h,view;
  char *t;
  float pos;
  char dir;
  mario_t* player;
} level_t;



void update(level_t *m);
level_t *loadLevel(char *filename);

