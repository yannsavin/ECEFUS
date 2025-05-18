#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "game.h"

void play(player_t *player[], game_t *game, spell_t ***spell){
    affichage(player, game, spell);
    while (!key[KEY_ESC]) {
        moove(player,game,spell);
        select_spell(player,game,spell);
        life(player,game);
        temps(player,game,spell);
        affichage(player,game,spell);
        rest(50);
        next(player,game,spell);
    }
}

void configurerpartie(game_t *game){
    BITMAP *nbjoueurs = load_bitmap("image/selection joueurs.bmp", NULL);
    stretch_blit(nbjoueurs, screen, 0, 0, nbjoueurs->w, nbjoueurs->h, 0, 0, SCREEN_W, SCREEN_H);
    game->nbplayers = 0;
    rest(50);

    while(game->nbplayers == 0) {
        if(mouse_b & 1){
            int x = mouse_x;
            int y = mouse_y;
            if(x >= 445 && x <= 1182 && y >= 265 && y <= 455){
                game->nbplayers = 2;
            } else if(x >= 445 && x <= 1182 && y >= 495 && y <= 690){
                game->nbplayers = 3;
            } else if(x >= 445 && x <= 1182 && y >= 730 && y <= 925){
                game->nbplayers = 4;
            }
            while(mouse_b & 1) { rest(10); }
        }
        rest(10);
    }

    destroy_bitmap(nbjoueurs);
}

void classe_pseudos(game_t *game, player_t *player[]){
    BITMAP *pseudo = load_bitmap("image/saisi pseudo.bmp", NULL);
    BITMAP *choixclasse = load_bitmap("image/choix class.bmp", NULL);
    stretch_blit(pseudo, screen, 0, 0, pseudo->w, pseudo->h, 0, 0, SCREEN_W, SCREEN_H);
    for(int i=0; i<game->nbplayers; i++) {
        char saisie[10] = "";
        int pos=0;
        while (1) {
            stretch_blit(pseudo, screen, 0, 0, pseudo->w, pseudo->h, 0, 0, SCREEN_W, SCREEN_H);
            textprintf_centre_ex(screen, font, 600, 570, makecol(255, 255, 255), -1, "%s", saisie);
            if (keypressed()) {
                int key = readkey() & 0xff;
                if (key==13 && pos>0) {
                    break;
                }
                else if (key == 8 && pos > 0) {
                    pos--;
                    saisie[pos] = '\0';
                }
                else if (pos < 10 && key >= 32 && key <= 126) {
                    saisie[pos++] = key;
                    saisie[pos] = '\0';
                }
            }
            rest(10);
        }
        strcpy(player[i]->name, saisie);
        stretch_blit(choixclasse, screen, 0, 0, choixclasse->w, choixclasse->h, 0, 0, SCREEN_W, SCREEN_H);
        int choisi = 0;
        while (!choisi) {
            if (mouse_b & 1) {
                int x = mouse_x;
                int y = mouse_y;
                if (x >= 95 && x <= 375 && y >= 255 && y <= 770) {
                    player[i]->classe = guerrier;
                    choisi = 1;
                } else if (x >= 410 && x <= 685 && y >= 255 && y <= 770) {
                    player[i]->classe = mage;
                    choisi = 1;
                } else if (x >= 725 && x <= 1000 && y >= 255 && y <= 770) {
                    player[i]->classe = assasin;
                    choisi = 1;
                } else if (x >= 1035 && x <= 1315 && y >= 255 && y <= 770) {
                    player[i]->classe = paladin;
                    choisi = 1;
                }
                while(mouse_b & 1) { rest(10); }
            }
        }

    }
    destroy_bitmap(pseudo);
    destroy_bitmap(choixclasse);
}

void menu_jeu(player_t *player[], game_t *game, spell_t ***spell,player_t *classe[]) {
    BITMAP *ecrantitre = load_bitmap("image/ecran start.bmp", NULL);
    BITMAP *menu = load_bitmap("image/menu2.bmp", NULL);
    BITMAP *ecranapres = load_bitmap("ecranapres.bmp", NULL);
    stretch_blit(ecrantitre, screen,0, 0, ecrantitre->w, ecrantitre->h, 0, 0, SCREEN_W, SCREEN_H);
    rest(50);
    while (!mouse_b & 1) {
        rest(10);
    }
    while (mouse_b & 1) {
        rest(10);
    }
    stretch_blit(menu, screen,0, 0, menu->w, menu->h, 0, 0, SCREEN_W, SCREEN_H);
    int quitter = 0;
    while (!quitter) {
        if (mouse_b & 1) {
            int x = mouse_x;
            int y = mouse_y;
            while (mouse_b & 1) {
                rest(10);
            }
            if (x >= 560 && x <= 1033 && y >= 460 && y <= 615) {
                configurerpartie(game);
                rest(100);
                classe_pseudos(game, player);
                initplayer(player, game, spell,classe);
                temps_restant=30;
                play(player, game, spell);
            }

            else if (x >= 560 && x <= 1033 && y >= 695 && y <= 845) {
                quitter = 1;
                allegro_exit();
            }
        }
        rest(10);
    }
    destroy_bitmap(ecrantitre);
    destroy_bitmap(menu);
}