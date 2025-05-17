#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"
#include "game.h"


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
        player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
        attaque(player, game, spell,src_y,src_x);
        player[game->tourjoueur]->action=0;

    }
}
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
            printf("%f\n",round(damage));
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
    int a = rand() % 101;
    if (a> spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->miss) {
        float min = spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMIN;
        float max = spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMAX;
        float miss = spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->miss;
        float damage = min + ((a - miss) / (100 - miss)) * (max - min);
        for (int i = 0; i < game->nbplayers; i++) {
            int px = player[i]->casex;
            int py = player[i]->casey;
            if (abs(px - src_x) <= 1 && abs(py - src_y) <= 1) {
                player[i]->health -= round(damage);
            }
        }
        player[game->tourjoueur]->healcd==1;
        player[game->tourjoueur]->incantation==1;
        return 1;
    }
}

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
int sendspell(player_t *player[],game_t *game,spell_t ***spell,int src_y,int src_x) {
        for (int i=0;i<4;i++) {
            draw_sprite(screen, spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->frame[i], (src_x*caseX)+decalageX+(10*i), (src_y*caseY)+decalageY+(10*i));
            rest(100);
            affichage(player,game,spell);
        }
        damagetaken(player,game,spell,src_y,src_x);
        player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
        player[game->tourjoueur]->action=0;
        affichage(player,game,spell);
        return 1;
}

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

int paladin_DEMACIA(player_t *player[],game_t *game,spell_t ***spell) {
    int a;
    float damage=0;
    a = rand()%101;
    if (a>spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->miss) {
        float min=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMIN;
        float max=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMAX+(player[game->tourjoueur]->stackDEMACIA)*2;
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

int mage_incnatation(player_t *player[],game_t *game,spell_t ***spell) {
    player[game->tourjoueur]->incantation=1;
    player[game->tourjoueur]->healcd=1;
    player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    player[game->tourjoueur]->action=0;
    affichage(player,game,spell);
    return 1;
}

int assasin_dodge(player_t *player[],game_t *game,spell_t ***spell) {
    player[game->tourjoueur]->dodge=1;
    player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    player[game->tourjoueur]->action=0;
    player[game->tourjoueur]->cleanscd=1;
    affichage(player,game,spell);
}

void place_spell(player_t *player[],game_t *game,spell_t ***spell) {
    int a=0,collisions=0;
    while(a==0) {
        int src_x = (mouse_x -decalageX)/caseX;
        int src_y = (mouse_y -decalageY)/caseY;
        affichage(player,game,spell);
        if(mouse_x > decalageX && mouse_y > decalageY && mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY){
            set_trans_blender(255, 0, 0, 128);
            draw_trans_sprite(screen, create_bitmap(caseX, caseY), (src_x*caseX)+decalageX, (src_y*caseY)+decalageY);
            if (mouse_b & 1 && player[game->tourjoueur]->classe!=2 &&
                abs(player[game->tourjoueur]->casex - src_x) <= spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->max &&
                abs(player[game->tourjoueur]->casey - src_y) <= spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->max &&
                (abs(player[game->tourjoueur]->casex - src_x) >= spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->min ||
                 abs(player[game->tourjoueur]->casey - src_y) >= spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->min)
                ){
                if (player[game->tourjoueur]->classe==3 && player[game->tourjoueur]->spellselect==1) {
                    player[game->tourjoueur]->stackDEMACIA+=1;
                }
                if (player[game->tourjoueur]->classe==3 && player[game->tourjoueur]->spellselect==0) {
                    a=paladin_stund(player,game,spell,src_y,src_x);
                    player[game->tourjoueur]->stackDEMACIA+=1;
                }
                else if(player[game->tourjoueur]->classe==0 && player[game->tourjoueur]->incantation==1 && player[game->tourjoueur]->spellselect==2 && player[game->tourjoueur]->healcd!=1) {
                    a=damagetakenAOE(player,game,spell,src_y,src_x);
                }
                else {
                    a=sendspell(player,game,spell,src_y,src_x);
                }
            }
            collisions=collision(player,game,src_x,src_y);
            if (mouse_b & 1 && player[game->tourjoueur]->classe==2 &&
                collisions==1 &&
                abs(player[game->tourjoueur]->casex - src_x) <= spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->max &&
                abs(player[game->tourjoueur]->casey - src_y) <= spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->max &&
                (abs(player[game->tourjoueur]->casex - src_x) >= spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->min ||
                abs(player[game->tourjoueur]->casey - src_y) >= spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->min)){
                assasin_tp(player,game,spell,src_y,src_x);
                affichage(player,game,spell);
                a=1;
            }
        }
        if (5<=mouse_x && 85>=mouse_x && (SCREEN_HEIGHT - 85)<=mouse_y && mouse_y<=SCREEN_HEIGHT-5) {
            if (mouse_b & 1) {
                player[game->tourjoueur]->action = 0;
                affichage(player,game,spell);
                a=1;

            }
        }
        rest(100);
    }
}

void repartitiontype(player_t *player[],game_t *game,spell_t ***spell) {
    if (player[game->tourjoueur]->spellselect!=-1) {
        rest(50);
        if (player[game->tourjoueur]->classe==0) {
            printf("%d %d\n",player[game->tourjoueur]->incantation,player[game->tourjoueur]->healcd);
            switch (player[game->tourjoueur]->spellselect) {
                case 0:
                    place_spell(player,game,spell);
                break;
                case 1:
                    place_spell(player,game,spell);
                break;
                case 2:
                if(player[game->tourjoueur]->incantation==0 && player[game->tourjoueur]->healcd==0) {
                    mage_incnatation(player,game,spell);
                }
                else if(player[game->tourjoueur]->incantation==1 && player[game->tourjoueur]->healcd==0) {
                    place_spell(player,game,spell);
                }
                else {
                    player[game->tourjoueur]->action=0;
                }
                break;
                case 3:
                    mage_cleans(player,game,spell);
                break;
            }
        }
        if (player[game->tourjoueur]->classe==1) {
            switch (player[game->tourjoueur]->spellselect) {
                case 0:
                    place_spell(player,game,spell);
                break;
                case 1:
                    berserk_heal(player,game,spell);
                break;
                case 2:
                    berserk_damage(player,game,spell);
                break;

            }
        }
        if (player[game->tourjoueur]->classe==2) {
            switch (player[game->tourjoueur]->spellselect) {
                case 0:
                    place_spell(player,game,spell);
                break;
                case 1:
                    assasin_buff(player,game,spell);
                break;
                case 2:
                    assasin_poison(player,game,spell);
                break;
                case 3:
                    if(player[game->tourjoueur]->dodge==0 && player[game->tourjoueur]->cleanscd==0) {
                        assasin_dodge(player,game,spell);
                    } else {player[game->tourjoueur]->action=0;}
                break;
            }
        }
        if (player[game->tourjoueur]->classe==3) {
            switch (player[game->tourjoueur]->spellselect) {
                case 0:
                    place_spell(player,game,spell);
                break;
                case 1:
                    place_spell(player,game,spell);
                break;
                case 2:
                    paladin_heal(player,game,spell);
                break;
                case 3:
                    paladin_DEMACIA(player,game,spell);
                break;
            }
        }
    }
}


void select_spell(player_t *player[],game_t *game,spell_t ***spell) {
     if (mouse_b & 1) {
         if (85<=mouse_x && 165>=mouse_x && 200<=mouse_y && mouse_y<=299){
            player[game->tourjoueur]->spellselect=0;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost) {
                 player[game->tourjoueur]->action=1;
                 repartitiontype(player,game,spell);
             }
             else {
                 player[game->tourjoueur]->spellselect=-1;
             }
        }
         if (85<=mouse_x && 165>=mouse_x && 300<=mouse_y && mouse_y<=399){
             player[game->tourjoueur]->spellselect=1;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost) {
                 player[game->tourjoueur]->action=1;
                 repartitiontype(player,game,spell);
             }
             else {
                 player[game->tourjoueur]->spellselect=-1;
             }
         }
         if (85<=mouse_x && 165>=mouse_x && 400<=mouse_y && mouse_y<=499){
             player[game->tourjoueur]->spellselect=2;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost) {
                 player[game->tourjoueur]->action=1;
                 repartitiontype(player,game,spell);
             }
             else  {
                 player[game->tourjoueur]->spellselect=-1;
             }
         }
         if (85<=mouse_x && 165>=mouse_x && 500<=mouse_y && mouse_y<=600){
             player[game->tourjoueur]->spellselect=3;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost) {
                 player[game->tourjoueur]->action=1;
                 repartitiontype(player,game,spell);
             }
             else  {
                 player[game->tourjoueur]->spellselect=-1;
             }
         }
    }
    if (mouse_b & 2) {
        if (85<=mouse_x && 165>=mouse_x && 200<=mouse_y && mouse_y<=299){
            game->conseille=0;
            affichage(player,game,spell);
        }
        else if (85<=mouse_x && 165>=mouse_x && 300<=mouse_y && mouse_y<=399){
            game->conseille=1;
            affichage(player,game,spell);
        }
        else if (85<=mouse_x && 165>=mouse_x && 400<=mouse_y && mouse_y<=499){
            game->conseille=2;
            affichage(player,game,spell);
        }
        else if (85<=mouse_x && 165>=mouse_x && 500<=mouse_y && mouse_y<=599){
            game->conseille=2;
            affichage(player,game,spell);
        }
        else game->conseille=-1;
    }
}
