#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"



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


void berserk_shild(player_t *player[],game_t *game,spell_t ***spell) {
    player[game->tourjoueur]->shild+=player[game->tourjoueur]->damage*2;
    player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    player[game->tourjoueur]->action=0;
    affichage(player,game,spell);
}

void repartitiontype(player_t *player[],game_t *game,spell_t ***spell) {
    if (player[game->tourjoueur]->spellselect!=-1) {
        rest(50);
        if (player[game->tourjoueur]->classe==0) {
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
                case 3:
                    berserk_shild(player,game,spell);
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
            game->conseille=3;
            affichage(player,game,spell);
        }
        else game->conseille=-1;
    }
}
