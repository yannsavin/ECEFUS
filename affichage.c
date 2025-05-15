#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"


int affichage(player_t *player[], game_t *game, spell_t ***spell) {
    rest(50);
    clear_bitmap(game->buffer);
    blit(game->map, game->buffer, 0, 0, decalageX, 0, 800, 800);
    for (int i = 0; i < game->nbplayers; i++) {
        if (player[i]->state==1) {
            player[i]->x = (player[i]->casex * caseX) + decalageX;
            player[i]->y = (player[i]->casey * caseY) + decalageY;
            draw_sprite(game->buffer, player[i]->skin, player[i]->x+10, player[i]->y+10);

        }
    }
    set_trans_blender(0, 0, 255, 40);
    int cx = player[game->tourjoueur]->casex;
    int cy = player[game->tourjoueur]->casey;
    if (player[game->tourjoueur]->action==0) {
        for (int dx = -player[game->tourjoueur]->PM; dx <= player[game->tourjoueur]->PM; dx++) {
            for (int dy = -player[game->tourjoueur]->PM; dy <= player[game->tourjoueur]->PM; dy++) {
                if (abs(dx) + abs(dy) <= player[game->tourjoueur]->PM && !(dx == 0 && dy == 0)) {
                    int nx = cx + dx;
                    int ny = cy + dy;
                    if (nx >= 0 && nx < nbcases && ny >= 0 && ny < nbcases && game->data[nx][ny]!=3 && game->data[nx][ny]!=4 &&
                    (nx != player[(game->tourjoueur+1)%3]->casex || ny != player[(game->tourjoueur+1)%3]->casey) &&
                    (nx != player[(game->tourjoueur+2)%3]->casex || ny != player[(game->tourjoueur+2)%3]->casey)) {
                        set_trans_blender(0, 0, 255, 100);
                        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
                        rectfill(game->buffer,(nx * caseX) + decalageX , (ny * caseY) + decalageY, (nx * caseX) + decalageX + caseX, (ny * caseY) + decalageY + caseY, makecol(0, 0, 255));
                        drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
                    }
                }
            }
        }
    }
    rectfill(game->buffer, 0, 0, 250, 800, makecol(0, 0, 0));
    draw_sprite(game->buffer, player[game->tourjoueur]->skin, 100, 0);

    textout_ex(game->buffer, font, "Tours de :", 10, 35, makecol(255, 255, 255), makecol(0, 0, 0));
    char buffer_text[64];
    sprintf(buffer_text, "%d", player[game->tourjoueur]->PM);
    textout_ex(game->buffer, font, buffer_text, 125, 130, makecol(255, 0, 0), makecol(0, 0, 0));
    sprintf(buffer_text, "%d", player[game->tourjoueur]->PA);
    textout_ex(game->buffer, font, buffer_text, 120, 150, makecol(0, 0, 255), makecol(0, 0, 0));
    sprintf(buffer_text, "%d", player[game->tourjoueur]->health);
    textout_ex(game->buffer, font, buffer_text, 115, 170, makecol(0, 255, 0), makecol(0, 0, 0));
    if (player[game->tourjoueur]) {
        int classe = player[game->tourjoueur]->classe;
        for (int i = 0; i < 3; i++) {
            int idx = i;
            if (idx >= 0) {
                draw_sprite(game->buffer, spell[classe][idx]->skin, 85, 200 + 100*i);
                sprintf(buffer_text, "%d", spell[classe][idx]->PAcost);
                textout_ex(game->buffer, font, buffer_text, 200, 245 + 100*i, makecol(0, 0, 255), makecol(0, 0, 0));
            }
        }
    }

    for (int i = 0; i < game->nbplayers; i++) {
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

    if (player[game->tourjoueur]->stackdamage>0 && player[game->tourjoueur]->classe==1) {
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
        sprintf(buffer_text, "%d",spell[player[game->tourjoueur]->classe][game->conseille]->damage);
        textout_ex(game->buffer, font, buffer_text, 100, 690, makecol(255, 0, 0), makecol(0, 0, 0));
        textout_ex(game->buffer, font, "damage", 120, 690, makecol(255, 255, 255), makecol(0, 0, 0));
        sprintf(buffer_text, "%d",spell[player[game->tourjoueur]->classe][game->conseille]->PAcost);
        textout_ex(game->buffer, font, buffer_text, 200, 690, makecol(0, 0, 255), makecol(0, 0, 0));
        textout_ex(game->buffer, font, "PA", 220, 690, makecol(255, 255, 255), makecol(0, 0, 0));
    }
    blit(game->buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    rectfill(screen, 265, SCREEN_HEIGHT - 85, 345, SCREEN_HEIGHT - 5, makecol(0, 255, 0));
    return 0;
}
