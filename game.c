#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "graphics.h"
#include "timer.h"
#include "game.h"
/* Principale fonction du jeu. Ne fait qu'appeler les fonctions dans les 
   autres fichiers */
int main(int argc, char *argv[]) {
  level_t *m;
  int finished=0;
  if (argc<2) {
    printf("Usage: mario <file>\n");
    exit(1); 
  }
  /* Charge les images des tuiles du jeu */
  loadSprites();
  /* Charge le plateau de jeu */
  m=loadLevel(argv[1]);
  /* Ouvre la fenetre */
  initWindow(m->view,m->h);
  /* Initialise le chronometre */
  timerInit();
  /* Tant que le jeu n'est pas fini */
  while(!finished) {
    /* Si on appuie sur une touche, le capture */
    finished=getEvent(m);
    /* Redessine le labyrinthe */
    paint(m);
    /* Met a jour le plateau de jeu */
    update(m);
    /* Attend un peu */
    timerWait();
  }
  return EXIT_SUCCESS;
}
