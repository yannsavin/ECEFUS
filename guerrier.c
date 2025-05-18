#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"

void berserk_heal(player_t *player[],game_t *game,spell_t ***spell) {
    player[game->tourjoueur]->health+=player[game->tourjoueur]->stackdamage;
    player[game->tourjoueur]->stackdamage=0;
    player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    player[game->tourjoueur]->action=0;
    affichage(player,game,spell);
}
void berserk_damage(player_t *player[],game_t *game,spell_t ***spell) {
    player[game->tourjoueur]->bonus=0;
    if (player[game->tourjoueur]->health<player[game->tourjoueur]->basehealth) {
        player[game->tourjoueur]->bonus=(10*(player[game->tourjoueur]->basehealth-player[game->tourjoueur]->health))/100;
        player[game->tourjoueur]->damage+=player[game->tourjoueur]->bonus;
        player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
        player[game->tourjoueur]->action=0;
        affichage(player,game,spell);
    }
}