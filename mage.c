#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"



void mage_cleans(player_t *player[],game_t *game,spell_t ***spell) {
    if (player[game->tourjoueur]->cleanscd==0) {
        player[game->tourjoueur]->cleanscd=1;
        if (player[game->tourjoueur]->stund==2) {
            player[game->tourjoueur]->PM=player[game->tourjoueur]->basePM;
        }
        if (player[game->tourjoueur]->poison==1) {
            player[game->tourjoueur]->poison=0;
            player[game->tourjoueur]->stack=0;
        }
        player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    }
    player[game->tourjoueur]->stund=0;
    player[game->tourjoueur]->action=0;
}
int mage_incnatation(player_t *player[],game_t *game,spell_t ***spell) {
    player[game->tourjoueur]->incantation=1;
    player[game->tourjoueur]->healcd=1;
    player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    player[game->tourjoueur]->action=0;
    affichage(player,game,spell);
    return 1;
}
