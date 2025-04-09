#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "game.h"




int damagetaken(player_t *player[],game_t *game, spell_t *spell[],int src_y,int src_x) {
    for(int i=0;i<3;i++) {
        if(player[i]->casex==src_x && player[i]->casey==src_y) {
            player[i]->health-=spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->damage;
            life(player);
        }
    }
}
int sendspell(player_t *player[],game_t *game,spell_t *spell[],int src_y,int src_x) {
        for (int i=0;i<4;i++) {
            draw_sprite(screen, spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->frame[i], (src_x*caseX)+decalageX+(10*i), (src_y*caseY)+decalageY+(10*i));
            rest(100);
            affichage(player,game,spell);
        }
        damagetaken(player,game,spell,src_y,src_x);
        player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->PAcost;
        affichage(player,game,spell);
        return 1;
}

void place_spell(player_t *player[],game_t *game,spell_t *spell[]) {
    int a=0;
    while(a==0) {
        int src_x = (mouse_x -decalageX)/caseX;
        int src_y = (mouse_y -decalageY)/caseY;
        affichage(player,game,spell);
        if(mouse_x > decalageX && mouse_y > decalageY && mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY){
            //rectfill(screen, (src_x*caseX)+420,(src_y*caseY)+90,(src_x*caseX)+420+caseX ,(src_y*caseY)+90+caseY, makecol(255,0,0));
            set_trans_blender(255, 0, 0, 128);
            draw_trans_sprite(screen, create_bitmap(caseX, caseY), (src_x*caseX)+decalageX, (src_y*caseY)+decalageY);
            if (mouse_b & 1) {
                a=sendspell(player,game,spell,src_y,src_x);
            }
        }
        rest(100);
    }
}

void select_spell(player_t *player[],game_t *game,spell_t *spell[]) {
     if (mouse_b & 1) {
         if (85<=mouse_x && 165>=mouse_x && 200<=mouse_y && mouse_y<=280){
            player[game->tourjoueur]->spellselect=0;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->PAcost) {
                 place_spell(player,game,spell);
             }
             else {
                 player[game->tourjoueur]->spellselect=-1;
             }
        }
         if (85<=mouse_x && 165>=mouse_x && 300<=mouse_y && mouse_y<=380){
             player[game->tourjoueur]->spellselect=1;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->PAcost) {
                 place_spell(player,game,spell);
             }
             else {
                 player[game->tourjoueur]->spellselect=-1;
             }
         }
         if (85<=mouse_x && 165>=mouse_x && 400<=mouse_y && mouse_y<=480){
             player[game->tourjoueur]->spellselect=2;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->PAcost) {
                 place_spell(player,game,spell);
             }
             else {
                 player[game->tourjoueur]->spellselect=-1;
             }
         }
    }
}
