#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"

void testpoison(player_t *player[],game_t *game, spell_t ***spell) {
    int a=0;
    float damage;
    a=rand() % 101;
    for (int i=0;i<game->nbplayers;i++) {
        if (player[i]->poison==1 && player[i]->stack<3) {
            float min=spell[2][0]->damageMIN;
            float max=spell[2][0]->damageMAX;
            float miss=spell[2][0]->miss;
            damage=min+((a-miss)/(100-miss))*(max-min);
            player[i]->health-=round(damage);
            player[i]->stack+=1;
        }
        if (player[i]->stack>3) {
            player[i]->stack=0;
            player[i]->poison=0;
        }
        if (player[i]->stack==3) {
            player[i]->stack+=1;
        }
    }
}

void damagetaken(player_t *player[],game_t *game, spell_t ***spell,int src_y,int src_x) {
    int a=0,b=0;
    float damage=0;
    a=rand() % 101;
    if (a>spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->miss) {
        for(int i=0;i<game->nbplayers;i++) {
            if(player[i]->casex==src_x && player[i]->casey==src_y) {
                float min=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMIN;
                float max=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMAX;
                float miss=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->miss;
                damage=min+((a-miss)/(100-miss))*(max-min);
                if (player[i]->dodge==1) {
                    b=rand() % 101;
                    if (b>50) {
                        player[i]->health-=round(damage);
                        player[i]->dodge=0;
                    }
                }
                else if (player[i]->classe==1 && player[i]->shild>0) {
                    player[i]->shild-=(damage);
                    if (player[i]->shild<0) {
                        player[i]->health+=player[i]->shild;
                        player[i]->shild=0;
                    }
                }
                else {
                    player[i]->health-=round(damage);
                }
                if(player[game->tourjoueur]->classe==1) {
                    player[i]->PM-=2;
                }
            }
        }
    }
}

int damagetakenAOE(player_t *player[], game_t *game, spell_t ***spell, int src_y, int src_x) {
    int a = rand() % 101,b=0;
    if (a> spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->miss) {
        float min = spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMIN;
        float max = spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMAX;
        float miss = spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->miss;
        float damage = min + ((a - miss) / (100 - miss)) * (max - min);
        for (int i = 0; i < game->nbplayers; i++) {
            int px = player[i]->casex;
            int py = player[i]->casey;
            if (abs(px - src_x) <= 1 && abs(py - src_y) <= 1) {
                if (player[i]->dodge==1) {
                    b=rand() % 101;
                    if (b>50) {
                        player[i]->health-=round(damage);
                        player[i]->dodge=0;
                    }
                }
                else if (player[i]->classe==1 && player[i]->shild>0) {
                    player[i]->shild-=(damage);
                    if (player[i]->shild<0) {
                        player[i]->health+=player[i]->shild;
                        player[i]->shild=0;
                    }
                }
                else {
                    player[i]->health-=round(damage);
                }
            }
        }
        player[game->tourjoueur]->healcd=1;
        player[game->tourjoueur]->incantation=1;
        return 1;
    }
}