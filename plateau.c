#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"


void skip(player_t *player[], game_t *game,spell_t **spell) {
    player[game->tourjoueur]->PA=player[game->tourjoueur]->basePA;
    player[game->tourjoueur]->PM=player[game->tourjoueur]->basePM;
    player[game->tourjoueur]->damage=player[game->tourjoueur]->basedamage;
    player[game->tourjoueur]->stackdamage=0;
    player[game->tourjoueur]->bonus=0;
    game->conseille=-1;
    game->tourjoueur++;
    if (game->tourjoueur>=3) {
        game->tourjoueur=0;}
    while (player[game->tourjoueur]->state==0) {
        game->tourjoueur++;
        if (game->tourjoueur>=3) {
            game->tourjoueur=0;
        }

    }
    affichage(player,game,spell);
}
void next(player_t *player[], game_t *game, spell_t **spell) {
    if (265<=mouse_x && 345>=mouse_x && (SCREEN_HEIGHT - 85)<=mouse_y && mouse_y<=SCREEN_HEIGHT-5){
        if (mouse_b & 1) {
            skip(player,game,spell);
        }
    }
}


void moove(player_t *player[],game_t *game,spell_t **spell) {
    if (mouse_b & 1 && player[game->tourjoueur]->PM >0){
        int src_x = (mouse_x -decalageX)/caseX;
        int src_y = (mouse_y -decalageY)/caseY;
        if (mouse_x > decalageX && mouse_y > decalageY &&
        mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY &&
        src_x - player[game->tourjoueur]->casex >= -1 &&
        src_x - player[game->tourjoueur]->casex <= 1 &&
        src_y - player[game->tourjoueur]->casey >= -1 &&
        src_y - player[game->tourjoueur]->casey <= 1 &&
        (src_x!=(player[(game->tourjoueur+1)%3]->casex) ||
        src_y!=(player[(game->tourjoueur+1)%3]->casey)) &&
        (src_x!=(player[(game->tourjoueur+2)%3]->casex) ||
        src_y!=(player[(game->tourjoueur+2)%3]->casey))) {
            player[game->tourjoueur]->casex=src_x;
            player[game->tourjoueur]->casey=src_y;
            player[game->tourjoueur]->PM-=1;
            affichage(player,game,spell);
        }
        else if (mouse_x > decalageX && mouse_y > decalageY &&
        mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY &&
        src_x - player[game->tourjoueur]->casex >= -1 &&
        src_x - player[game->tourjoueur]->casex <= 1 &&
        src_y - player[game->tourjoueur]->casey >= -1 &&
        src_y - player[game->tourjoueur]->casey <= 1) {
            for (int i=0; i<3; i++) {
                if (src_x==player[i]->casex && src_y==player[i]->casey && player[game->tourjoueur]->PA>=2) {
                    player[i]->health-=player[game->tourjoueur]->damage;
                    player[game->tourjoueur]->PA-=player[game->tourjoueur]->attaquecost;
                    player[game->tourjoueur]->stackdamage+=player[game->tourjoueur]->damage;
                    affichage(player,game,spell);
                }
            }
        }
    }
}
int life(player_t *player[]) {
    for (int i = 0; i < 3; i++) {
        if(player[i]->health<=0) {
        player[i]->state=0;
        }
    }
}
