#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
#include "graphics.h"
/* Charge le plateau de jeu. Prend un nom de fichier en parametre, retourne un 
  pointeur sur une structure level definie dans engine.h
*/
level_t *loadLevel(char *filename) {
  level_t *m;

  m = malloc(sizeof(level_t));	//Allocation
  m->player = malloc(sizeof(mario_t));

  m->player[0].mario_w=SIZE2;
  m->player[0].mario_h=SIZE;

  m->score=0;
  m->deplacement_monstres = 0;
  
  m->player[0].nb_kill = 0;
  m->tocard = false;

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
			  case 'a': m->t[m->w*i+j]=MONSTER_A; break;
			  case 'b': m->t[m->w*i+j]=MONSTER_B; break;
			  case 'c': m->t[m->w*i+j]=MONSTER_C; break;
			  default: m->t[m->w*i+j]= EMPTY;
			}
			
		  }	  
		  
	  }

  
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
	
	
	//Gestion du "temps" score
	m->score++;
	
	
	
	// le personnage tombe
	if (m->t[m->w*(m->player[0].mario_y + 1)+m->player[0].mario_x] == EMPTY){
		m->player[0].mario_y++;
	}	
	if (m->t[m->w*(m->player[0].mario_y + 1)+m->player[0].mario_x] == GROUND) {
		m->player[0].mario_y++;
	}
	if ((m->t[m->w*(m->player[0].mario_y + 1)+m->player[0].mario_x] == MONSTER_A)
	 ||(m->t[m->w*(m->player[0].mario_y + 1)+m->player[0].mario_x] == MONSTER_B)
	 ||(m->t[m->w*(m->player[0].mario_y + 1)+m->player[0].mario_x] == MONSTER_C)) {
		 
		m->t[m->w*(m->player[0].mario_y + 1)+m->player[0].mario_x] = EMPTY;
		playKillSound();
	}
	if (m->t[m->w*(m->player[0].mario_y + 1)+m->player[0].mario_x] == WATER){
		m->player[0].mario_y++;
		m->tocard = true;
		quitterJeu(m);
	}
	if (m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x] == MONSTER_A
	|| m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x] == MONSTER_B
	|| m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x] == MONSTER_C){
		m->tocard = true;
		quitterJeu(m);
	}
	if (m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x] == DOOR){
		m->tocard = false;
		quitterJeu(m);
	}
	if (m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x] == BONUS1){
		m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x] = EMPTY;
		playBonusSound();
		m->score *= 0.75;
	}
	if (m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x] == BONUS2){
		m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x] = EMPTY;
		playBonusSound();
		m->player[0].nb_kill++;
	}
	//Deplacement mario gauche droite
	if (m->player[0].dir == LEFT && m->pos > 0 ){
		m -> pos --; 
		m->player[0].mario_x--;
		}
	if (m->player[0].dir == RIGHT && m->pos < m->w ){
		m -> pos ++; 
		m->player[0].mario_x++;
		}
		
		
		switch(m->t[(m->w * (m->player[0].mario_y + 1))+m->player[0].mario_x])
		{
			case UPGRASS1 : 
				m->player[0].mario_x ++;
				m->player[0].mario_y --;
				m -> pos ++;
				break;
			case DOWNGRASS2 :
				if( m->player[0].dir == LEFT)
				{
					m->player[0].mario_y --;
				}	
				break;
			default:;
		}
		
		//Déplacement des monstres
	if (m->deplacement_monstres % 5 == 0)
	{
		deplMonstre(m);
	}
	m->deplacement_monstres++;
}

//Deplacement monstres
void deplMonstre(level_t*m)
{	
	int i;
	int j;
	
	  for (i = 0; i < m->h; i++)
	  {
		  for (j = m->pos; j < (m->pos + m -> view) ; j++)
		  {
				if (m->t[m->w*i+j] == MONSTER_A
				||  m->t[m->w*i+j] == MONSTER_B
				||  m->t[m->w*i+j] == MONSTER_C){
					int deplacement = rand()%2;
					if (deplacement == 0)
					{
						if (m->t[m->w*(i+1)+(j-1)] == GRASS && m->t[m->w*(i)+(j-1)] == EMPTY)
						{
							m->t[m->w*i+j-1] = m->t[m->w*i+j];
							m->t[m->w*i+j] = EMPTY;
						}
					}
					else
					{
						if (m->t[m->w*(i+1)+(j+1)] == GRASS && m->t[m->w*(i)+(j+1)] == EMPTY)
						{
							m->t[m->w*i+j+1] = m->t[m->w*i+j];
							m->t[m->w*i+j] = EMPTY;
						}
					}						
				}
			}
		}
}

void mario_KillMonstersBonus2(level_t* m)
{
	
	int i;
	for (i = 0; i < m->view; i++)
	{
		if ((m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x+i] == MONSTER_A
		|| m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x+i] == MONSTER_B
		|| m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x+i] == MONSTER_C)
		&& m->player[0].nb_kill > 0
		)
		{
			m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x+i] = EMPTY;
			playKillSound();
			m->player[0].nb_kill--;
			break;
		}
		else if (m->t[m->w*(m->player[0].mario_y)+m->player[0].mario_x+i] != EMPTY)
		{
			break;
		}
	}
	
}

void quitterJeu(level_t *m)
{
	if (m->tocard)
	{
		printf("TOCARD\n");
	}
	else
	{
		printf("GAGNE\n");
	}
	printf("NB KILL : %d\n", m->player[0].nb_kill);
	printf("Score : %d\n", m->score);
	exit(0);
}
