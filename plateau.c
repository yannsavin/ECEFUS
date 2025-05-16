#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "game.h"


void skip(player_t *player[], game_t *game,spell_t ***spell) {
    player[game->tourjoueur]->PA=player[game->tourjoueur]->basePA;
    player[game->tourjoueur]->PM=player[game->tourjoueur]->basePM;
    player[game->tourjoueur]->damage=player[game->tourjoueur]->basedamage;
    player[game->tourjoueur]->stackdamage=0;
    player[game->tourjoueur]->bonus=0;
    player[game->tourjoueur]->action==0;
    game->conseille=-1;
    game->tourjoueur++;
    if (game->tourjoueur>=3) {
        game->tourjoueur=0;
        testpoison(player,game,spell);
    }
    while (player[game->tourjoueur]->state==0) {
        game->tourjoueur++;
        if (game->tourjoueur>=3) {
            game->tourjoueur=0;
        }
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
    for (int i=0; i<3; i++) {
        if (src_x==player[i]->casex && src_y==player[i]->casey && player[game->tourjoueur]->PA>=2) {
            if(player[game->tourjoueur]->classe==2 && player[game->tourjoueur]->poisondag==1) {
                player[i]->poison=1;
                player[game->tourjoueur]->poisondag=0;
                testpoison(player,game,spell);
            }
            if(player[game->tourjoueur]->classe==2 && player[game->tourjoueur]->buff==1) {
                player[i]->health-=player[game->tourjoueur]->damage*2;
                printf("%d\n",player[game->tourjoueur]->damage*2);
                player[game->tourjoueur]->buff=0;
            }
            else {
                player[i]->health-=player[game->tourjoueur]->damage;
                printf("%d\n",player[game->tourjoueur]->damage);
            }
            player[game->tourjoueur]->PA-=player[game->tourjoueur]->attaquecost;
            player[game->tourjoueur]->stackdamage+=player[game->tourjoueur]->damage;
            affichage(player,game,spell);
        }
    }
}

void moove(player_t *player[],game_t *game,spell_t ***spell) {
    if (mouse_b & 1 && player[game->tourjoueur]->PM >0 && player[game->tourjoueur]->action==0) {
        int a=0,b=0;
        int src_x = (mouse_x -decalageX)/caseX;
        int src_y = (mouse_y -decalageY)/caseY;
        int vecteurx=-(player[game->tourjoueur]->casex-src_x);
        int vecteury=-(player[game->tourjoueur]->casey-src_y);
        int deplacement=abs(vecteurx)+abs(vecteury);
        int nextx=0;
        int nexty=0;
        if (mouse_x > decalageX && mouse_y > decalageY &&
        mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY && deplacement<=player[game->tourjoueur]->PM &&
            (src_x != player[(game->tourjoueur+1)%3]->casex  || src_y != player[(game->tourjoueur+1)%3]->casey)&&
            (src_x != player[(game->tourjoueur+2)%3]->casex ||  src_y != player[(game->tourjoueur+2)%3]->casey)) {
            for (int i=0 ; i<deplacement ; i++) {
                if (vecteurx==0) {
                    a=1;
                }
                if (vecteury==0) {
                    a=0;
                }
                if(b>2) {
                    deplacement=i;
                }
                if (vecteurx!=0 && a==0) {
                    nextx=player[game->tourjoueur]->casex+(vecteurx/abs(vecteurx));
                    if ((nextx != player[(game->tourjoueur+1)%3]->casex  || player[game->tourjoueur]->casey != player[(game->tourjoueur+1)%3]->casey)&&
                    (nextx != player[(game->tourjoueur+2)%3]->casex ||  player[game->tourjoueur]->casey != player[(game->tourjoueur+2)%3]->casey)&&
                    game->data[nextx][player[game->tourjoueur]->casey]!=3 && game->data[nextx][player[game->tourjoueur]->casey]!=4) {
                        b=0;
                        player[game->tourjoueur]->casex+=vecteurx/abs(vecteurx);
                        player[game->tourjoueur]->PM-=1;
                        vecteurx+=-vecteurx/abs(vecteurx);
                        affichage(player, game, spell);
                    }
                    else {a=1;deplacement+=1;b+=1;}
                }
                else if (vecteury!=0 && a==1) {
                    nexty=player[game->tourjoueur]->casey+(vecteury/abs(vecteury));
                    if ((nexty != player[(game->tourjoueur+1)%3]->casey || player[game->tourjoueur]->casex != player[(game->tourjoueur+1)%3]->casex) &&
                    (nexty != player[(game->tourjoueur+2)%3]->casey || player[game->tourjoueur]->casex != player[(game->tourjoueur+2)%3]->casex) &&
                    game->data[player[game->tourjoueur]->casex][nexty]!=3 && game->data[player[game->tourjoueur]->casex][nexty]!=4) {
                        b=0;
                        player[game->tourjoueur]->casey+=vecteury/abs(vecteury);
                        player[game->tourjoueur]->PM-=1;
                        vecteury+=-vecteury/abs(vecteury);
                        affichage(player, game, spell);
                    }
                    else {a=0;deplacement+=1;b+=1;}
                }
                rest(100);
            }
        }
        else if (mouse_x > decalageX && mouse_y > decalageY &&
            mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY &&
            src_x - player[game->tourjoueur]->casex >= -1 &&
            src_x - player[game->tourjoueur]->casex <= 1 &&
            src_y - player[game->tourjoueur]->casey >= -1 &&
            src_y - player[game->tourjoueur]->casey <= 1) {
            attaque(player, game, spell,src_y,src_x);
        }
    }
}
void life(player_t *player[]) {
    for (int i = 0; i < 3; i++) {
        if(player[i]->health<=0) {
        player[i]->state=0;
        }
    }
}
