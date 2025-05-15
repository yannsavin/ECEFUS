#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"
#include "game.h"




void damagetaken(player_t *player[],game_t *game, spell_t ***spell,int src_y,int src_x) {
    int a=0;
    float damage=0;
    a=rand() % 101;
    if (a>spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->miss && player[game->tourjoueur]->classe!=assasin) {
        for(int i=0;i<game->nbplayers;i++) {
            if(player[i]->casex==src_x && player[i]->casey==src_y) {
                float min=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMIN;
                float max=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->damageMAX;
                float miss=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->miss;
                damage=min+((a-miss)/(100-miss))*(max-min);
                printf("\n%f\n%f\n%f\n%f\n%f\n",round(a),min,max,miss,damage);
                player[i]->health-=round(damage);
                if(player[game->tourjoueur]->classe==1) {
                    player[i]->PM-=2;
                }
                life(player);
            }
        }
    }
    if (player[game->tourjoueur]->classe!=assasin) {
        
    }
}

void berserk_heal(player_t *player[],game_t *game,spell_t ***spell) {
    player[game->tourjoueur]->health+=player[game->tourjoueur]->stackdamage;
    player[game->tourjoueur]->stackdamage=0;
    player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
    affichage(player,game,spell);
}
void berserk_damage(player_t *player[],game_t *game,spell_t ***spell) {
    player[game->tourjoueur]->bonus=0;
    if (player[game->tourjoueur]->health<player[game->tourjoueur]->basehealth) {
        player[game->tourjoueur]->bonus=(10*(player[game->tourjoueur]->basehealth-player[game->tourjoueur]->health))/100;
        player[game->tourjoueur]->damage+=player[game->tourjoueur]->bonus;
        player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost;
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
        affichage(player,game,spell);
        return 1;
}


void place_spell(player_t *player[],game_t *game,spell_t ***spell) {
    int a=0;
    while(a==0) {
        int src_x = (mouse_x -decalageX)/caseX;
        int src_y = (mouse_y -decalageY)/caseY;
        affichage(player,game,spell);
        if(mouse_x > decalageX && mouse_y > decalageY && mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY){
            set_trans_blender(255, 0, 0, 128);
            draw_trans_sprite(screen, create_bitmap(caseX, caseY), (src_x*caseX)+decalageX, (src_y*caseY)+decalageY);
            if (mouse_b & 1 &&
                abs(player[game->tourjoueur]->casex - src_x) <= spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->max &&
                abs(player[game->tourjoueur]->casey - src_y) <= spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->max &&
                (abs(player[game->tourjoueur]->casex - src_x) > spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->min ||
                 abs(player[game->tourjoueur]->casey - src_y) > spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->min)
                ){
                a=sendspell(player,game,spell,src_y,src_x);
            }
        }
        rest(100);
    }
}

void repartitiontype(player_t *player[],game_t *game,spell_t ***spell) {
    if (player[game->tourjoueur]->spellselect!=-1) {
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
        if (player[game->tourjoueur]->classe==0) {
            if (spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->type==0) {
                place_spell(player,game,spell);
            }
        }
    }
}


void select_spell(player_t *player[],game_t *game,spell_t ***spell) {
     if (mouse_b & 1) {
         if (85<=mouse_x && 165>=mouse_x && 200<=mouse_y && mouse_y<=280){
            player[game->tourjoueur]->spellselect=0;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost) {
                 repartitiontype(player,game,spell);
             }
             else {
                 player[game->tourjoueur]->spellselect=-1;
             }
        }
         if (85<=mouse_x && 165>=mouse_x && 300<=mouse_y && mouse_y<=380){
             player[game->tourjoueur]->spellselect=1;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost) {
                 repartitiontype(player,game,spell);
             }
             else {
                 player[game->tourjoueur]->spellselect=-1;
             }
         }
         if (85<=mouse_x && 165>=mouse_x && 400<=mouse_y && mouse_y<=480){
             player[game->tourjoueur]->spellselect=2;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->PAcost) {
                 repartitiontype(player,game,spell);
             }
             else  {
                 player[game->tourjoueur]->spellselect=-1;
             }
         }
    }
    if (mouse_b & 2) {
        if (85<=mouse_x && 165>=mouse_x && 200<=mouse_y && mouse_y<=280){
            game->conseille=0;
            affichage(player,game,spell);
        }
        if (85<=mouse_x && 165>=mouse_x && 300<=mouse_y && mouse_y<=380){
            game->conseille=1;
            affichage(player,game,spell);
        }
        if (85<=mouse_x && 165>=mouse_x && 400<=mouse_y && mouse_y<=480){
            game->conseille=2;
            affichage(player,game,spell);
        }
        else game->conseille=-1;
    }
}
