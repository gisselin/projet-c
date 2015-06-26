#include <stdbool.h>
#define SIZE 70
#define SIZE2 44
#define NB_MARIOS 22

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
  MONSTER_A,
  MONSTER_B,
  MONSTER_C,
  NTILES
  
};

enum {
  NONE=0,
  LEFT,
  RIGHT
};




typedef struct {
	int mario_x,mario_y,mario_w,mario_h;
	char dir;
	bool alive;
	int nb_kill;
} mario_t;

typedef struct {
	int mon_x,mon_y,mon_w,mon_h;
	char dir;
} monster_t;

typedef struct {
  int w,h,view;
  char *t;
  float pos;
  int score;
  int deplacement_monstres;
  bool tocard;
  monster_t* monsters;
  mario_t* player;
} level_t;

void mario_KillMonstersBonus2(level_t* m);
void quitterJeu(level_t *m);

void update(level_t *m);
level_t *loadLevel(char *filename);
void deplMonstre(level_t*m);


