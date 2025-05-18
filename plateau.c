#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "game.h"


int collision(player_t *player[],game_t *game,int x, int y) {
    for (int i = 0; i < game->nbplayers; i++) {
        if (i != game->tourjoueur && player[i]->casex ==x && player[i]->casey == y) {
            return 1;
        }
    }
    return 0;
}

void temps(player_t *player[], game_t *game,spell_t ***spell) {
    if (temps_restant <=0) {
        skip(player,game,spell);
    }
}

void skip(player_t *player[], game_t *game,spell_t ***spell) {
    player[game->tourjoueur]->PA=player[game->tourjoueur]->basePA;
    player[game->tourjoueur]->PM=player[game->tourjoueur]->basePM;
    player[game->tourjoueur]->damage=player[game->tourjoueur]->basedamage;
    player[game->tourjoueur]->stackdamage=0;
    player[game->tourjoueur]->bonus=0;
    player[game->tourjoueur]->action==0;
    temps_restant = 30;
    game->conseille=-1;
    game->tourjoueur++;
    if (game->tourjoueur>=game->nbplayers) {
        game->tourjoueur=0;
        testpoison(player,game,spell);
    }
    while (player[game->tourjoueur]->state==0) {
        game->tourjoueur++;
        if (game->tourjoueur>=game->nbplayers) {
            game->tourjoueur=0;
        }
    }
    if( player[game->tourjoueur]->ccimune==1) {
        player[game->tourjoueur]->ccimune=0;
        player[game->tourjoueur]->stund=0;
    }
    if( player[game->tourjoueur]->stund==2) {
        player[game->tourjoueur]->stund=0;
    }
    if( player[game->tourjoueur]->stund==1) {
        player[game->tourjoueur]->stund=2;
        player[game->tourjoueur]->ccimune=1;
        player[game->tourjoueur]->PM=0;
    }
    if(player[game->tourjoueur]->healcd==1) {
        player[game->tourjoueur]->healcd=0;
    }
    if(player[game->tourjoueur]->cleanscd==2) {
        player[game->tourjoueur]->cleanscd=0;
    }
    if(player[game->tourjoueur]->cleanscd==1) {
        player[game->tourjoueur]->cleanscd=2;
    }
    if(player[game->tourjoueur]->bonusPM==1) {
        player[game->tourjoueur]->PM+=2;
        player[game->tourjoueur]->bonusPM=0;
    }
    affichage(player,game,spell);
    rest(50);
}
void next(player_t *player[], game_t *game, spell_t ***spell) {
    if (265<=mouse_x && 345>=mouse_x && (SCREEN_HEIGHT - 85)<=mouse_y && mouse_y<=SCREEN_HEIGHT-5){
        if (mouse_b & 1) {
            skip(player,game,spell);
        }
    }
}

void attaque(player_t *player[], game_t *game, spell_t ***spell,int src_y,int src_x) {
    int damage=player[game->tourjoueur]->damage,b;
    for (int i=0; i<3; i++) {
        if (src_x==player[i]->casex && src_y==player[i]->casey && player[game->tourjoueur]->PA>=2) {
            if(player[game->tourjoueur]->classe==2 && player[game->tourjoueur]->poisondag==1) {
                player[i]->poison=1;
                player[game->tourjoueur]->poisondag=0;
                testpoison(player,game,spell);
            }
            if(player[game->tourjoueur]->classe==2 && player[game->tourjoueur]->buff==1) {
                damage*=2;
            }
            if (player[i]->dodge==1) {
                b=rand() % 101;
                if (b>50) {
                    player[i]->health-=(damage);
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
                player[i]->health-=damage;
            }
            player[game->tourjoueur]->buff=0;

            player[game->tourjoueur]->PA-=player[game->tourjoueur]->attaquecost;
            player[game->tourjoueur]->stackdamage+=player[game->tourjoueur]->damage;
            affichage(player,game,spell);
        }
    }
}
void deplacement_fluide(player_t *p, int dest_case_x, int dest_case_y, game_t *game, player_t *player[], spell_t ***spell) {
    int start_x = p->pixel_x;
    int start_y = p->pixel_y;
    int end_x = dest_case_x * caseX + decalageX;
    int end_y = dest_case_y * caseY + decalageY;

    int frames = 10;
    for (int i = 1; i <= frames; i++) {
        float t = (float)i / frames;
        p->pixel_x = start_x + (end_x - start_x) * t;
        p->pixel_y = start_y + (end_y - start_y) * t;
        affichage(player, game, spell);
        rest(5);
    }
    p->casex = dest_case_x;
    p->casey = dest_case_y;
    p->pixel_x = end_x;
    p->pixel_y = end_y;
}

void moove(player_t *player[], game_t *game, spell_t ***spell) {
    if (mouse_b & 1 && player[game->tourjoueur]->PM > 0 && player[game->tourjoueur]->action == 0) {
        int src_x = (mouse_x - decalageX) / caseX;
        int src_y = (mouse_y - decalageY) / caseY;
        int vecteurx = src_x - player[game->tourjoueur]->casex;
        int vecteury = src_y - player[game->tourjoueur]->casey;
        int deplacement = abs(vecteurx) + abs(vecteury);
        int collisions = collision(player, game, src_x, src_y);
        if (mouse_x > decalageX && mouse_y > decalageY &&
            mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY &&
            deplacement <= player[game->tourjoueur]->PM &&
            collisions != 1) {
            while (vecteurx != 0 || vecteury != 0) {
                int step_x = (vecteurx != 0) ? vecteurx / abs(vecteurx) : 0;
                int step_y = (vecteury != 0) ? vecteury / abs(vecteury) : 0;
                if (abs(vecteurx) >= abs(vecteury) && step_x != 0) {
                    int nx = player[game->tourjoueur]->casex + step_x;
                    int cy = player[game->tourjoueur]->casey;
                    collisions = collision(player, game, nx, cy);
                    if (collisions != 1 && game->data[nx][cy] != 3 && game->data[nx][cy] != 4) {
                        deplacement_fluide(player[game->tourjoueur], nx, cy, game, player, spell);
                        player[game->tourjoueur]->PM -= 1;
                        vecteurx -= step_x;
                    } else {
                        break;
                    }
                } else if (step_y != 0) {
                    int ny = player[game->tourjoueur]->casey + step_y;
                    int cx = player[game->tourjoueur]->casex;
                    collisions = collision(player, game, cx, ny);
                    if (collisions != 1 && game->data[cx][ny] != 3 && game->data[cx][ny] != 4) {
                        deplacement_fluide(player[game->tourjoueur], cx, ny, game, player, spell);
                        player[game->tourjoueur]->PM -= 1;
                        vecteury -= step_y;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
        } else if (mouse_x > decalageX && mouse_y > decalageY &&
                   mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY &&
                   src_x - player[game->tourjoueur]->casex >= -1 &&
                   src_x - player[game->tourjoueur]->casex <= 1 &&
                   src_y - player[game->tourjoueur]->casey >= -1 &&
                   src_y - player[game->tourjoueur]->casey <= 1 &&
                   player[game->tourjoueur]->PA >= player[game->tourjoueur]->attaquecost) {

            attaque(player, game, spell, src_y, src_x);
        }
    }
}

void life(player_t *player[], game_t *game) {
    for (int i = 0; i < game->nbplayers; i++) {
        if(player[i]->health<=0) {
        player[i]->state=0;
        }
    }
}
