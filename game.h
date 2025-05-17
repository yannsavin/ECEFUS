//
// Created by yann on 29/03/2025.
//

#ifndef GAME_H
#define GAME_H
#include <allegro/gfx.h>

#define mage 0
#define guerrier 1
#define assasin 2
#define paladin 3
#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 800
#define caseX 100
#define caseY 100
#define decalageX 350
#define decalageY 0
#define nbcases 8

typedef struct game {
    int conseille;
    int nbplayers;
    int tourjoueur,action, n_map;
    int data[8][8];
    BITMAP *cases[4][5];
    BITMAP *map;
    BITMAP *buffer;
}game_t;

typedef struct player {
    int state,action,stund,ccimune,healcd,cleanscd,bonusPM,stackDEMACIA;
    int spellselect,classe,incantation,dodge;
    char name[20];
    int number,PA,basePA,PM,basePM,attaquecost;
    int spelltab[4];
    int casex,casey,bonus;
    int poison,stack,poisondag,buff;
    int x,y;
    int health,basehealth,damage,basedamage,armor;
    int stackdamage,skinnum;
    BITMAP *skin;
    BITMAP *skinclass[5];
}player_t;
typedef struct spell {
    char name[50];
    int damage,PAcost,count;
    int damageMAX,damageMIN,miss;
    int type,min,max;
    BITMAP *skin;
    BITMAP *frame[4];
}spell_t;

void initialisation_allegro(game_t *game);
void init_map(game_t *game);
void init(player_t *player[],game_t *game, spell_t ***spell,player_t *class[]);
int affichage(player_t *player[], game_t *game, spell_t ***spell);
void destroy(player_t *player[],game_t *game,spell_t ***spell);
void damagetaken(player_t *player[],game_t *game, spell_t ***spell,int src_y,int src_x);
int sendspell(player_t *player[],game_t *game,spell_t ***spell,int src_y,int src_x);
void place_spell(player_t *player[],game_t *game,spell_t ***spell);
void select_spell(player_t *player[],game_t *game,spell_t ***spell);
void life(player_t *player[],game_t *game);
void moove(player_t *player[],game_t *game,spell_t ***spell);
void skip(player_t *player[], game_t *game,spell_t ***spell);
void next(player_t *player[], game_t *game, spell_t ***spell);
void testpoison(player_t *player[],game_t *game, spell_t ***spell);
void attaque(player_t *player[], game_t *game, spell_t ***spell,int src_y,int src_x);
void initplayer(player_t *player[],game_t *game, spell_t ***spell,player_t *classe[]);
void play(player_t *player[], game_t *game, spell_t ***spell);
void menu_jeu(player_t *player[], game_t *game, spell_t ***spell,player_t *classe[]);
void configurerpartie(game_t *game);
void classe_pseudos(game_t *game, player_t *player[]);
int collision(player_t *player[],game_t *game,int x, int y);
#endif //GAME_H

