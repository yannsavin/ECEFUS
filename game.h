//
// Created by yann on 29/03/2025.
//

#ifndef GAME_H
#define GAME_H
#include <allegro/gfx.h>

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 800
#define caseX 100
#define caseY 100
#define decalageX 350
#define decalageY 0
#define nbcases 8

typedef struct game {
    int nbplayers;
    int tourjoueur,action;
    BITMAP *cases[5];
    BITMAP *map;
    BITMAP *buffer;
}game_t;

typedef struct player {
    int state;
    int spellselect,classe;
    char name[50];
    int number,PA,basePA,PM,basePM,attaquecost;
    int spelltab[4];
    int casex,casey;
    int x,y;
    int health,damage,armor;
    int stackdamage;
    BITMAP *skin;
}player_t;
typedef struct spell {
    char name[50];
    int damage,PAcost,count;
    int type;
    BITMAP *skin;
    BITMAP *frame[4];
}spell_t;

void initialisation_allegro(game_t *game);
void init_map(game_t *game);
void init(player_t *player[],game_t *game, spell_t **spell);
int affichage(player_t *player[], game_t *game, spell_t **spell);
void destroy(player_t *player[],game_t *game,spell_t **spell);
int damagetaken(player_t *player[],game_t *game, spell_t **spell,int src_y,int src_x);
int sendspell(player_t *player[],game_t *game,spell_t **spell,int src_y,int src_x);
void place_spell(player_t *player[],game_t *game,spell_t **spell);
void select_spell(player_t *player[],game_t *game,spell_t **spell);
int life(player_t *player[]);
void moove(player_t *player[],game_t *game,spell_t **spell);
void skip(player_t *player[], game_t *game,spell_t **spell);
void next(player_t *player[], game_t *game, spell_t **spell);
#endif //GAME_H

