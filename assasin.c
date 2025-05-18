#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"

void assasin_dodge(player_t *player[],game_t *game,spell_t ***spell) {
    player[game->tourjoueur]->dodge=1;
    player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    player[game->tourjoueur]->action=0;
    player[game->tourjoueur]->cleanscd=1;
    affichage(player,game,spell);
}

void assasin_buff(player_t *player[],game_t *game, spell_t ***spell) {
    player[game->tourjoueur]->buff=1;
    player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    player[game->tourjoueur]->action=0;
    affichage(player,game,spell);
}

void assasin_poison(player_t *player[],game_t *game, spell_t ***spell) {
    player[game->tourjoueur]->poisondag=1;
    player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    player[game->tourjoueur]->action=0;
    affichage(player,game,spell);
}

void assasin_tp(player_t *player[],game_t *game,spell_t ***spell,int src_y,int src_x) {
    int a=0,b=0;
    int casex=0,casey=0,collisions;
    if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost) {
        while(a==0) {
            b=rand()%4;
            switch(b) {
                case 0:
                    casex=src_x+1;
                    casey=src_y;
                    collisions=collision(player,game,casex,casey);
                    if (collisions!=1 && game->data[casex][casey]!=3 && game->data[casex][casey]!=4 && casex<8 && casey<8 && casex>=0 && casey>=0) {
                        player[game->tourjoueur]->casex=casex;
                        player[game->tourjoueur]->casey=casey;
                        a=1;
                    }
                    break;
                case 1:
                    casex=src_x-1;
                    casey=src_y;
                    collisions=collision(player,game,casex,casey);
                    if (collisions!=1 && game->data[casex][casey]!=3 && game->data[casex][casey]!=4 && casex<8 && casey<8 && casex>=0 && casey>=0) {
                        player[game->tourjoueur]->casex=casex;
                        player[game->tourjoueur]->casey=casey;
                        a=1;
                    }
                    break;
                case 2:
                    casex=src_x;
                    casey=src_y+1;
                    collisions=collision(player,game,casex,casey);
                    if (collisions!=1 && game->data[casex][casey]!=3 && game->data[casex][casey]!=4 && casex<8 && casey<8 && casex>=0 && casey>=0) {
                        player[game->tourjoueur]->casex=casex;
                        player[game->tourjoueur]->casey=casey;
                        a=1;
                    }
                    break;
                case 3:
                    casex=src_x;
                    casey=src_y-1;
                    collisions=collision(player,game,casex,casey);
                    if (collisions!=1 && game->data[casex][casey]!=3 && game->data[casex][casey]!=4 && casex<8 && casey<8 && casex>=0 && casey>=0) {
                        player[game->tourjoueur]->casex=casex;
                        player[game->tourjoueur]->casey=casey;
                        a=1;
                    }
                    break;
            }
        }
        player[game->tourjoueur]->pixel_x = player[game->tourjoueur]->casex * caseX + decalageX;
        player[game->tourjoueur]->pixel_y = player[game->tourjoueur]->casey * caseY + decalageY;
        affichage(player,game,spell);
        player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
        attaque(player, game, spell,src_y,src_x);
        player[game->tourjoueur]->action=0;
    }
}
