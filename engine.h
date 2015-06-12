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
  BONUS,
  NTILES
  
};

enum {
  NONE=0,
  LEFT,
  RIGHT
};

typedef struct {
  int w,h,view;
  char **t;
  float pos;
  char dir;
} level_t;


void update(level_t *m);
level_t *loadLevel(char *filename);

