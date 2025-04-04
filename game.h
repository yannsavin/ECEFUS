//
// Created by yann on 29/03/2025.
//

#ifndef GAME_H
#define GAME_H
#include <allegro/gfx.h>

typedef struct game {
    int nbplayers;
    int tourjoueur,action;
    BITMAP *cases[5];
}game_t;

typedef struct player {
    int state;
    int spellselect;
    char name[50];
    int number,PA,basePA,PM,basePM;
    int spelltab[3];
    int casex,casey;
    int x,y;
    int health,damage,armor;
    BITMAP *skin;
}player_t;
typedef struct spell {
    char name[50];
    int damage,PAcost;
    BITMAP *skin;
    BITMAP *frame[4];
}spell_t;


#endif //GAME_H
