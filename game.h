#ifndef GAME_H
#define GAME_H

#include <allegro/gfx.h>

#define mage 0
#define guerrier 1
#define assasin 2
#define paladin 3
#define SCREEN_WIDTH 1700
#define SCREEN_HEIGHT 960
#define caseX 80
#define caseY 80
#define decalageX 350
#define decalageY 0
#define nbcases 12

extern volatile int temps_restant;

typedef struct game {
    int conseille;
    int nbplayers,rank;
    int tourjoueur,action, n_map;
    int data[nbcases][nbcases];
    BITMAP *cases[4][5];
    BITMAP *map;
    BITMAP *buffer;
}game_t;

typedef struct player {
    int state,action,stund,ccimune,healcd,cleanscd,bonusPM,stackDEMACIA;
    int spellselect,classe,incantation,dodge;
    char name[20];
    int number,PA,basePA,PM,basePM,attaquecost;
    int nb_skins,rang;
    int casex,casey,bonus;
    int poison,stack,poisondag,buff;
    int x,y,pixel_x,pixel_y;
    int health,basehealth,damage,basedamage,shild;
    int stackdamage,skinnum;
    BITMAP *skin;
    BITMAP *skinclass[2];
    BITMAP *affichage[2];
}player_t;

typedef struct spell {
    char name[50];
    int damage,PAcost,count;
    int damageMAX,damageMIN,miss;
    int type,min,max;
    BITMAP *skin;
    BITMAP *frame[4];
}spell_t;

void initialisation_allegro(game_t *game);   //initialisation allegro
void init_map(game_t *game, const char *nom_fichier) ;              //initiallisation map
void init(player_t *player[],game_t *game, spell_t ***spell,player_t *class[]); //appelle toutes les fonction d'initialisation (player,class,spell)
int affichage(player_t *player[], game_t *game, spell_t ***spell);   //affichage du jeux (map,perso,hud)
void destroy(player_t *player[],game_t *game,spell_t ***spell);     //detruit les bitmap et libere l'espace a la fin du programme
void damagetaken(player_t *player[],game_t *game, spell_t ***spell,int src_y,int src_x);   //verrifie si des degats sont subit
int sendspell(player_t *player[],game_t *game,spell_t ***spell,int src_y,int src_x);       //envoie d'un sort avec annimation
void place_spell(player_t *player[],game_t *game,spell_t ***spell);                         //placer un sort
void select_spell(player_t *player[],game_t *game,spell_t ***spell);                        // selectionner un sort dans la barre d'action
void life(player_t *player[],game_t *game);                                                  //verrifie si le joueur est en vie
void moove(player_t *player[],game_t *game,spell_t ***spell);                                //mouvement du joueur
void skip(player_t *player[], game_t *game,spell_t ***spell);                               // passer au joueur suivant
void next(player_t *player[], game_t *game, spell_t ***spell);                              // passe au joueur suivant si le temps est ecoule
void testpoison(player_t *player[],game_t *game, spell_t ***spell);                         //verrifie si le joueur est empoisonee
void attaque(player_t *player[], game_t *game, spell_t ***spell,int src_y,int src_x);          // attaque au corps a corps
void initplayer(player_t *player[],game_t *game, spell_t ***spell,player_t *classe[]);          //initialisation joueur
void play(player_t *player[], game_t *game, spell_t ***spell,player_t *classe[]);               // boucle du jeux
void menu_jeu(player_t *player[], game_t *game, spell_t ***spell,player_t *classe[]);           //menu du jeux
void configurerpartie(game_t *game);                                                             //configurer la partie
void classe_pseudos(game_t *game, player_t *player[],player_t *classe[]);                       //saisie de la classe et du pseudo
int collision(player_t *player[],game_t *game,int x, int y);                                    //teste de colision
void temps(player_t *player[], game_t *game,spell_t ***spell);                                  //defillement du temps
void assasin_tp(player_t *player[],game_t *game,spell_t ***spell,int src_y,int src_x);          //teleportation de l'assasin
void assasin_buff(player_t *player[],game_t *game, spell_t ***spell);                           //sort d'augmentation de degat de l'assasin
void assasin_poison(player_t *player[],game_t *game, spell_t ***spell);                        //sort d'empoisonnement sur la prochaine attaque de l'assasin
void berserk_heal(player_t *player[],game_t *game,spell_t ***spell);                           //sort de heal du guerrier
void berserk_damage(player_t *player[],game_t *game,spell_t ***spell);                         // sort d'augmentation de degats en fonction de la vie manquante du guerrier
int paladin_stund(player_t *player[],game_t *game,spell_t ***spell,int src_y,int src_x);        //sort d'immobilisation du paladin
int paladin_heal(player_t *player[],game_t *game,spell_t ***spell);                             //sort de soin + PM du paladin
void mage_cleans(player_t *player[],game_t *game,spell_t ***spell);                             // sort de dissipation des effet negatif du mage
int paladin_DEMACIA(player_t *player[],game_t *game,spell_t ***spell);                          //sort ultime du paladin
int mage_incnatation(player_t *player[],game_t *game,spell_t ***spell);                         //verrifier l'incantation du mage pour sort 3
void assasin_dodge(player_t *player[],game_t *game,spell_t ***spell);                           // sort d'esquive de l'assasin
void berserk_shild(player_t *player[],game_t *game,spell_t ***spell);                           //sort de shild du guerrier en fonction de ses degats
int damagetakenAOE(player_t *player[], game_t *game, spell_t ***spell, int src_y, int src_x);   // verrifie les damages pour le sort aoe
void set_transparence(BITMAP *bmp, int r, int g, int b);                                        //mettre les bitmap en transparent
void fin(player_t *player[], game_t *game, spell_t ***spell,player_t *classe[]);                //fin du jeux
#endif //GAME_H