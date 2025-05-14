#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "game.h"


int affichage(player_t *player[], game_t *game, spell_t **spell) {
    rest(50);
    clear_bitmap(game->buffer);
    blit(game->map, game->buffer, 0, 0, decalageX, 0, 800, 800);
    for (int i = 0; i < 3; i++) {
        if (player[i]->state==1) {
            player[i]->x = (player[i]->casex * caseX) + decalageX;
            player[i]->y = (player[i]->casey * caseY) + decalageY;
            draw_sprite(game->buffer, player[i]->skin, player[i]->x+10, player[i]->y+10);
        }
    }
    set_trans_blender(0, 0, 255, 40);
    int cx = player[game->tourjoueur]->casex;
    int cy = player[game->tourjoueur]->casey;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (!(dx == 0 && dy == 0)) {
                int nx = cx + dx;
                int ny = cy + dy;
                if (nx >= 0 && nx < nbcases && ny >= 0 && ny < nbcases) {
                    draw_trans_sprite(game->buffer, create_bitmap(caseX, caseY), (nx * caseX) + decalageX, (ny * caseY) + decalageY);
                }
            }
        }
    }
    rectfill(game->buffer, 0, 0, 250, 800, makecol(0, 0, 0));
    draw_sprite(game->buffer, player[game->tourjoueur]->skin, 100, 0);

    textout_ex(game->buffer, font, "Tours de :", 10, 35, makecol(255, 255, 255), makecol(0, 0, 0));
    char buffer_text[10];
    sprintf(buffer_text, "%d", player[game->tourjoueur]->PM);
    textout_ex(game->buffer, font, buffer_text, 125, 130, makecol(255, 0, 0), makecol(0, 0, 0));
    sprintf(buffer_text, "%d", player[game->tourjoueur]->PA);
    textout_ex(game->buffer, font, buffer_text, 120, 150, makecol(0, 0, 255), makecol(0, 0, 0));
    sprintf(buffer_text, "%d", player[game->tourjoueur]->health);
    textout_ex(game->buffer, font, buffer_text, 115, 170, makecol(0, 255, 0), makecol(0, 0, 0));
    for (int i = 0; i < 3; i++) {
        draw_sprite(game->buffer, spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spelltab[i]].skin, 85, 200+100*i);
        sprintf(buffer_text, "%d", spell[player[game->tourjoueur]->classe][i].PAcost);
        textout_ex(game->buffer, font, buffer_text, 200, 245+100*i, makecol(0, 0, 255), makecol(0, 0, 0));
    }
    for (int i = 0; i < 3; i++) {
        if (player[i]->state==1) {
            draw_sprite(game->buffer, player[i]->skin, 1400, i*200);
            sprintf(buffer_text, "%d", player[i]->health);
            textout_ex(game->buffer, font, buffer_text, 1250, i*200+35, makecol(0, 255, 0), makecol(0, 0, 0));
            sprintf(buffer_text, "%d", player[i]->PM);
            textout_ex(game->buffer, font, buffer_text, 1300, i*200+35, makecol(255, 0,0 ), makecol(0, 0, 0));
            sprintf(buffer_text, "%d", player[i]->PA);
            textout_ex(game->buffer, font, buffer_text, 1350, i*200+35, makecol(0, 0, 255), makecol(0, 0, 0));
        }
    }

    if (player[game->tourjoueur]->stackdamage>0) {
        sprintf(buffer_text, "%d", player[game->tourjoueur]->stackdamage);
        textout_ex(game->buffer, font, buffer_text, 230, 345, makecol(255, 0, 0), makecol(0, 0, 0));
    }
    if (player[game->tourjoueur]->bonus>0) {
        sprintf(buffer_text, "%d", player[game->tourjoueur]->bonus);
        textout_ex(game->buffer, font, buffer_text, 230, 445, makecol(255, 0, 0), makecol(0, 0, 0));
    }
    if (player[game->tourjoueur]->classe==0) {
        switch (game->conseille) {
            case 0:
                textout_ex(game->buffer, font, "Sort de degats d'eau ",75, 650, makecol(255, 255, 255), makecol(0, 0, 0));
            break;
            case 1:
                textout_ex(game->buffer, font, "Sort de degats de feu", 75, 650, makecol(255, 255, 255), makecol(0, 0, 0));
            break;
            case 2:
                textout_ex(game->buffer, font, "Sort de degats de foudre degats de zone", 25, 650, makecol(255, 255, 255), makecol(0, 0, 0));
                textout_ex(game->buffer, font, "(1 case autour) et 2 tour pour incanter", 25, 670, makecol(255, 255, 255), makecol(0, 0, 0));
            break;
        }
    }
    if (game->conseille>=0) {
        sprintf(buffer_text, "%d",spell[player[game->tourjoueur]->classe][game->conseille].damage);
        textout_ex(game->buffer, font, buffer_text, 100, 690, makecol(255, 0, 0), makecol(0, 0, 0));
        textout_ex(game->buffer, font, "damage", 120, 690, makecol(255, 255, 255), makecol(0, 0, 0));
        sprintf(buffer_text, "%d",spell[player[game->tourjoueur]->classe][game->conseille].PAcost);
        textout_ex(game->buffer, font, buffer_text, 200, 690, makecol(0, 0, 255), makecol(0, 0, 0));
        textout_ex(game->buffer, font, "PA", 220, 690, makecol(255, 255, 255), makecol(0, 0, 0));
    }
    blit(game->buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    rectfill(screen, 265, SCREEN_HEIGHT - 85, 345, SCREEN_HEIGHT - 5, makecol(0, 255, 0));
}
