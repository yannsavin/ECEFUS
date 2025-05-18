#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"

int paladin_stund(player_t *player[],game_t *game,spell_t ***spell,int src_y,int src_x) {
    for (int i=0;i<game->nbplayers;i++) {
        if (player[i]->casex==src_x && player[i]->casey==src_y) {
            player[i]->stund=1;
        }
    }
    player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    player[game->tourjoueur]->action=0;
    affichage(player,game,spell);
    return 1;
}

int paladin_heal(player_t *player[],game_t *game,spell_t ***spell) {
    if (player[game->tourjoueur]->healcd==0) {
        player[game->tourjoueur]->health+=50;
        player[game->tourjoueur]->healcd=1;
        player[game->tourjoueur]->bonusPM=1;
        player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
        player[game->tourjoueur]->stackDEMACIA+=1;
    }
    player[game->tourjoueur]->action=0;
    return 1;
}

int paladin_DEMACIA(player_t *player[],game_t *game,spell_t ***spell) {
    int a;
    float damage=0;
    a = rand()%101;
    BITMAP *temp = create_bitmap(SCREEN_W, SCREEN_H);
    if (a>spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->miss) {
        for (int i=0;i<=700;i+=20) {
            clear_bitmap(temp);
            blit(game->buffer, temp, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            draw_sprite(temp, spell[paladin][3]->frame[0], 700, -500+i);
            blit(temp, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(15);
        }
        rest(1000);
        float min=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMIN+(player[game->tourjoueur]->stackDEMACIA)*5;
        float max=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMAX+(player[game->tourjoueur]->stackDEMACIA)*5;
        float miss=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->miss;
        damage=min+((a-miss)/(100-miss))*(max-min);
        for (int i=0;i<game->nbplayers;i++) {
            if (i!=game->tourjoueur) {
                player[i]->health-=round(damage);
            }
        }
    }
    player[game->tourjoueur]->stackDEMACIA=0;
    player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    player[game->tourjoueur]->action=0;
    affichage(player,game,spell);
}