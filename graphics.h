/* Charge les images des tuiles pouvant décrire le plateau de jeu */
void loadSprites();
/* Dessine le plateau de jeu dans la fenetre */
void paint(level_t *l);
/* Initialise la fenetre de jeu. w et h sont la largeur et la hauteur
   du plateau de jeu, en nombre de tuiles. */
void initWindow(int w,int h);
/* Gere les pressions de touche clavier, et divers evenements */
int getEvent(level_t *l) ;
/*Fonction action case */
void actionsCases(level_t *m);
