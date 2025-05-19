#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

void set_transparence(BITMAP *bmp, int r, int g, int b) {
    int color = makecol(r, g, b);
    for (int y = 0; y < bmp->h; y++) {
        for (int x = 0; x < bmp->w; x++) {
            if (getpixel(bmp, x, y) == color) {
                putpixel(bmp, x, y, bitmap_mask_color(bmp));
            }
        }
    }
}

int affichage_peros_map(player_t *player[], game_t *game, spell_t ***spell) {
    char buffer_text[64];
    for (int i = 0; i < game->nbplayers; i++) {
        if (player[i]->state==1) {
            set_transparence(player[i]->skin,0,0,0);
            draw_sprite(game->buffer, player[i]->skin, player[i]->pixel_x, player[i]->pixel_y);
            if (player[i]->stund==1 || player[i]->stund==2) {
                draw_sprite(game->buffer, spell[paladin][0]->frame[0], player[i]->pixel_x, player[i]->pixel_y);
            }
        }
    }
    sprintf(buffer_text, "%s", player[game->tourjoueur]->name);
    if (game->n_map==1 || game->n_map==3) {
        textout_ex(game->buffer, font, buffer_text, player[game->tourjoueur]->pixel_x+20, player[game->tourjoueur]->pixel_y, makecol(255, 0, 255), -1);
    }
    else {textout_ex(game->buffer, font, buffer_text, player[game->tourjoueur]->pixel_x+20, player[game->tourjoueur]->pixel_y, makecol(255, 255, 0), -1);}

}

int scoreboard(player_t *player[], game_t *game, spell_t ***spell) {
    char buffer_text[64];
    for (int i = 0; i < game->nbplayers; i++) {
        if (player[i]->state==1) {
            draw_sprite(game->buffer, player[i]->skin, SCREEN_W-100, i*200);
            sprintf(buffer_text, "%d", player[i]->health);
            textout_ex(game->buffer, font, buffer_text, SCREEN_W-250, i*200+35, makecol(0, 255, 0), makecol(0, 0, 0));
            sprintf(buffer_text, "%d", player[i]->PM);
            textout_ex(game->buffer, font, buffer_text, SCREEN_W-180, i*200+35, makecol(255, 0,0 ), makecol(0, 0, 0));
            sprintf(buffer_text, "%d", player[i]->PA);
            textout_ex(game->buffer, font, buffer_text, SCREEN_W-150, i*200+35, makecol(0, 0, 255), makecol(0, 0, 0));
            sprintf(buffer_text, "%s", player[i]->name);
            textout_ex(game->buffer, font, buffer_text, SCREEN_W-70, i*200+130, makecol(255, 255, 255), makecol(0, 0, 0));
            if (player[i]->poison==1) {
                textout_ex(game->buffer, font, "poison", SCREEN_W-250, i*200+95, makecol(255, 255, 255), makecol(0, 0, 0));
                sprintf(buffer_text, "%d", player[game->tourjoueur]->stack);
                textout_ex(game->buffer, font, buffer_text, SCREEN_W-200, i*200+95, makecol(255, 255, 0), makecol(0, 0, 0));
            }
            if (player[i]->stund==2 || player[i]->stund==1) {
                textout_ex(game->buffer, font, "stund", SCREEN_W-150, i*200+95, makecol(255, 255,0), makecol(0, 0, 0));
            }
            if (player[i]->classe==assasin) {
                textout_ex(game->buffer, font, "esquive :", SCREEN_W-250, i*200+65, makecol(255, 255, 255), makecol(0, 0, 0));
                if(player[i]->dodge==1) {
                    textout_ex(game->buffer, font, "active", SCREEN_W-170, i*200+65, makecol(0, 255, 0), makecol(0, 0, 0));
                }
                else {
                    textout_ex(game->buffer, font, "inactive", SCREEN_W-170, i*200+65, makecol(255, 0, 0), makecol(0, 0, 0));
                }
            }
            if (player[i]->shild>0) {
                textout_ex(game->buffer, font, "+", SCREEN_W-225, i*200+35, makecol(143, 143, 138 ), makecol(0, 0, 0));
                sprintf(buffer_text, "%d", player[i]->shild);
                textout_ex(game->buffer, font, buffer_text, SCREEN_W-215, i*200+35, makecol(143, 143, 138 ), makecol(0, 0, 0));
            }
        }
    }
}

int info_joueurs(player_t *player[], game_t *game, spell_t ***spell) {
    char buffer_text[64];
    sprintf(buffer_text, "%d", temps_restant);
    textout_ex(game->buffer, font, buffer_text, 250, 50, makecol(255, 255, 255),makecol(0, 0, 0) );
    rectfill(game->buffer, 0, 0, 250, 800, makecol(0, 0, 0));
    draw_sprite(game->buffer, player[game->tourjoueur]->skin, 100, 0);
    textout_ex(game->buffer, font, "Tours de :", 10, 35, makecol(255, 255, 255), makecol(0, 0, 0));
    sprintf(buffer_text, "%d", player[game->tourjoueur]->PM);
    textout_ex(game->buffer, font, buffer_text, 125, 130, makecol(255, 0, 0), makecol(0, 0, 0));
    sprintf(buffer_text, "%d", player[game->tourjoueur]->PA);
    textout_ex(game->buffer, font, buffer_text, 120, 150, makecol(0, 0, 255), makecol(0, 0, 0));
    sprintf(buffer_text, "%d", player[game->tourjoueur]->health);
    textout_ex(game->buffer, font, buffer_text, 115, 170, makecol(0, 255, 0), makecol(0, 0, 0));
    sprintf(buffer_text, "%s", player[game->tourjoueur]->name);
    textout_ex(game->buffer, font, buffer_text, 250, 30, makecol(255, 255, 255), makecol(0, 0, 0));
}

int affichage_spells(player_t *player[], game_t *game, spell_t ***spell) {
    char buffer_text[64];
    if (player[game->tourjoueur]->shild>0) {
        textout_ex(game->buffer, font, "+", 140, 170, makecol(143, 143, 138 ), makecol(0, 0, 0));
        sprintf(buffer_text, "%d", player[game->tourjoueur]->shild);
        textout_ex(game->buffer, font, buffer_text, 150, 170, makecol(143, 143, 138 ), makecol(0, 0, 0));
    }
    if (player[game->tourjoueur]->poison==1) {
        textout_ex(game->buffer, font, "poison", 200, 130, makecol(255, 255, 255), makecol(0, 0, 0));
        sprintf(buffer_text, "%d", player[game->tourjoueur]->stack);
        textout_ex(game->buffer, font, buffer_text, 250, 130, makecol(255, 255, 0), makecol(0, 0, 0));
    }
    if (player[game->tourjoueur]->stund==2) {
        textout_ex(game->buffer, font, "stund", 200, 160, makecol(255, 255,0), makecol(0, 0, 0));
    }
    if (player[game->tourjoueur]->classe==paladin) {
        if (player[game->tourjoueur]->healcd==0) {
            textout_ex(game->buffer, font, "up", 230, 445, makecol(0, 255, 0), makecol(0, 0, 0));
        }
        else {
            textout_ex(game->buffer, font, "no", 230, 445, makecol(255, 0, 0), makecol(0, 0, 0));
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
    if (player[game->tourjoueur]->stackDEMACIA>0) {
        sprintf(buffer_text, "%d", player[game->tourjoueur]->stackDEMACIA);
        textout_ex(game->buffer, font, buffer_text, 230, 545, makecol(255, 0, 0), makecol(0, 0, 0));
    }
    if (player[game->tourjoueur]->classe==assasin && player[game->tourjoueur]->dodge==1) {
        textout_ex(game->buffer, font, "active", 250, 545, makecol(255, 255, 0), makecol(0, 0, 0));
    }
    if (player[game->tourjoueur]->classe==assasin || player[game->tourjoueur]->classe==mage) {
        if (player[game->tourjoueur]->cleanscd==0) {
            textout_ex(game->buffer, font, "up", 230, 545, makecol(0, 255, 0), makecol(0, 0, 0));
        }
        else {
            textout_ex(game->buffer, font, "no", 230, 545, makecol(255, 0, 0), makecol(0, 0, 0));
        }
    }
    if (player[game->tourjoueur]->classe==mage && player[game->tourjoueur]->incantation==1) {
        if (player[game->tourjoueur]->healcd==0) {
            textout_ex(game->buffer, font, "ready", 220, 445, makecol(0, 255, 0), makecol(0, 0, 0));
        }
        if (player[game->tourjoueur]->healcd==1) {
            textout_ex(game->buffer, font, "start", 220, 445, makecol(255, 255, 0), makecol(0, 0, 0));
        }
    }
    if (player[game->tourjoueur]) {
        int classe = player[game->tourjoueur]->classe;
        for (int i = 0; i < 4; i++) {
            int idx = i;
            if (idx >= 0) {
                draw_sprite(game->buffer, spell[classe][idx]->skin, 85, 200 + 100*i);
                sprintf(buffer_text, "%d", spell[classe][idx]->PAcost);
                textout_ex(game->buffer, font, buffer_text, 200, 245 + 100*i, makecol(0, 0, 255), makecol(0, 0, 0));
            }
        }
    }

}

int affichage_range_spells(player_t *player[], game_t *game, spell_t ***spell) {
    if (player[game->tourjoueur]->action == 1) {
        int nx = player[game->tourjoueur]->casex;
        int ny = player[game->tourjoueur]->casey;
        int min = spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->min;
        int max = spell[player[game->tourjoueur]->classe][player[game->tourjoueur]->spellselect]->max;
        for (int i = 0; i < nbcases; i++) {
            for (int j = 0; j < nbcases; j++) {
                int dx = abs(nx - j);
                int dy = abs(ny - i);
                if (dx <= max && dy <= max && (dx >= min || dy >= min)) {
                    set_trans_blender(255, 0, 0, 100);
                    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
                    rectfill(game->buffer,
                             (j * caseX) + decalageX,
                             (i * caseY) + decalageY,
                             (j * caseX) + decalageX + caseX,
                             (i * caseY) + decalageY + caseY,
                             makecol(255, 0, 0));
                    drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
                }
            }
        }
    }
}

int affichage_range_moovement(player_t *player[], game_t *game, spell_t ***spell) {
    set_trans_blender(0, 0, 255, 40);
    int cx = player[game->tourjoueur]->casex;
    int cy = player[game->tourjoueur]->casey;
    int collisions=0;
    if (player[game->tourjoueur]->action==0 && mouse_x > decalageX && mouse_y > decalageY && mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY) {
        for (int dx = -player[game->tourjoueur]->PM; dx <= player[game->tourjoueur]->PM; dx++) {
            for (int dy = -player[game->tourjoueur]->PM; dy <= player[game->tourjoueur]->PM; dy++) {
                if (abs(dx) + abs(dy) <= player[game->tourjoueur]->PM && !(dx == 0 && dy == 0)) {
                    int nx = cx + dx;
                    int ny = cy + dy;
                    collisions= collision(player,game,nx,ny);
                    if (nx >= 0 && nx < nbcases && ny >= 0 && ny < nbcases && game->data[nx][ny]!=3 && game->data[nx][ny]!=4 &&
                    collisions!=1) {
                        set_trans_blender(0, 0, 255, 100);
                        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
                        rectfill(game->buffer,(nx * caseX) + decalageX , (ny * caseY) + decalageY, (nx * caseX) + decalageX + caseX, (ny * caseY) + decalageY + caseY, makecol(0, 0, 255));
                        drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
                    }
                }
            }
        }
    }
}

int affichage_conseille(player_t *player[], game_t *game, spell_t ***spell) {
    char buffer_text[64];
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
        if (spell[player[game->tourjoueur]->classe][game->conseille]->damageMIN>0) {
            sprintf(buffer_text, "%d",spell[player[game->tourjoueur]->classe][game->conseille]->damageMIN);
            textout_ex(game->buffer, font, buffer_text, 73+35, 690, makecol(255, 0, 0), makecol(0, 0, 0));
            textout_ex(game->buffer, font, "-", 90+35, 690, makecol(255, 255, 255), makecol(0, 0, 0));
            sprintf(buffer_text, "%d",spell[player[game->tourjoueur]->classe][game->conseille]->damageMAX);
            textout_ex(game->buffer, font, buffer_text, 100+35, 690, makecol(255, 0, 0), makecol(0, 0, 0));
            textout_ex(game->buffer, font, "damage", 120+35, 690, makecol(255, 255, 255), makecol(0, 0, 0));
        }
        if (spell[player[game->tourjoueur]->classe][game->conseille]->min!=0 && spell[player[game->tourjoueur]->classe][game->conseille]->min!=0) {
            sprintf(buffer_text, "%d",spell[player[game->tourjoueur]->classe][game->conseille]->min);
            textout_ex(game->buffer, font, buffer_text, 93+55, 710, makecol(255, 255, 0), makecol(0, 0, 0));
            textout_ex(game->buffer, font, "-", 100+55, 710, makecol(255, 255, 255), makecol(0, 0, 0));
            sprintf(buffer_text, "%d",spell[player[game->tourjoueur]->classe][game->conseille]->max);
            textout_ex(game->buffer, font, buffer_text, 110+55, 710, makecol(255, 255, 0), makecol(0, 0, 0));
            textout_ex(game->buffer, font, "range", 120+55, 710, makecol(255, 255, 255), makecol(0, 0, 0));
        }
        sprintf(buffer_text, "%d",spell[player[game->tourjoueur]->classe][game->conseille]->PAcost);
        textout_ex(game->buffer, font, buffer_text, 200+25, 690, makecol(0, 0, 255), makecol(0, 0, 0));
        textout_ex(game->buffer, font, "PA", 210+25, 690, makecol(255, 255, 255), makecol(0, 0, 0));

    }
}

int affichage(player_t *player[], game_t *game, spell_t ***spell) {
    rest(50);

    clear_bitmap(game->buffer);
    blit(game->map, game->buffer, 0, 0, decalageX, 0, 960, 960);
    affichage_conseille(player, game, spell);
    affichage_peros_map(player, game, spell);
    scoreboard(player, game, spell);
    info_joueurs(player, game, spell);
    affichage_spells(player, game, spell);
    affichage_range_spells(player, game, spell);
    affichage_range_moovement(player, game, spell);
    affichage_conseille(player, game, spell);

    if (player[game->tourjoueur]->action == 1) {
        rectfill(game->buffer, 5, SCREEN_HEIGHT - 85, 85, SCREEN_HEIGHT - 5, makecol(255, 0, 0));
    }
    if (player[game->tourjoueur]->action == 0) {
        rectfill(game->buffer, 5, SCREEN_HEIGHT - 85, 85, SCREEN_HEIGHT - 5, makecol(0, 0, 0));
    }
    blit(game->buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    rectfill(screen, 265, SCREEN_HEIGHT - 85, 345, SCREEN_HEIGHT - 5, makecol(0, 255, 0));
    return 0;
}