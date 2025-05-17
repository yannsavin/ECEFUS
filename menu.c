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
        affichage(player,game,spell);
        rest(50);
        next(player,game,spell);
    }
}

void configurerpartie(game_t *game){
    BITMAP *nbjoueurs = load_bitmap("nbjoueurs.bmp", NULL);
    stretch_blit(nbjoueurs, screen,0, 0, nbjoueurs->w, nbjoueurs->h, 0, 0, SCREEN_W, SCREEN_H);
    game->nbplayers=0;
    printf("%d\n",game->nbplayers);
    rect(screen,265,355,365,455,makecol(255,255,255));
    rect(screen,715,355,815,455,makecol(255,255,255));
    rect(screen,1170,355,1270,455,makecol(255,255,255));
    while(game->nbplayers==0) {
        if(mouse_b & 1){
            printf("essaie\n");
            int x=mouse_x;
            int y=mouse_y;
            if(x >= 265 && x <= 365 && y >= 355 && y <= 455){
                game->nbplayers=2;
                printf("%d\n",game->nbplayers);
            }
            if(x >= 715 && x <= 815 && y >= 355 && y <= 455){
                game->nbplayers=3;
                printf("%d\n",game->nbplayers);
            }
            if(x >= 1170 && x <= 1270 && y >= 355 && y <= 455){
                game->nbplayers=4;
                printf("%d\n",game->nbplayers);
            }
        }
        rest(50);
    }

    destroy_bitmap(nbjoueurs);

}

void classe_pseudos(game_t *game, player_t *player[]){
    BITMAP *pseudo = load_bitmap("pseudo.bmp", NULL);
    BITMAP *choixclasse = load_bitmap("choixclasse.bmp", NULL);
    stretch_blit(pseudo, screen, 0, 0, pseudo->w, pseudo->h, 0, 0, SCREEN_W, SCREEN_H);
    for(int i=0; i<game->nbplayers; i++) {
        char saisie[10] = "";
        int pos=0;
        while (1) {
            stretch_blit(pseudo, screen, 0, 0, pseudo->w, pseudo->h, 0, 0, SCREEN_W, SCREEN_H);
            textprintf_centre_ex(screen, font, SCREEN_W / 2, 500, makecol(255, 255, 255), -1, "%s", saisie);
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
                if (x >= 60 && x <= 190 && y >= 355 && y <= 455) {
                    player[i]->classe = assasin;
                    choisi = 1;
                } else if (x >= 475 && x <= 605 && y >= 355 && y <= 455) {
                    player[i]->classe = guerrier;
                    choisi = 1;
                } else if (x >= 905 && x <= 1035 && y >= 355 && y <= 455) {
                    player[i]->classe = mage;
                    choisi = 1;
                } else if (x >= 1260 && x <= 1390 && y >= 355 && y <= 455) {
                    player[i]->classe = paladin;
                    choisi = 1;
                }
            }
        }
        printf("%s\n",player[i]->name);
        printf("%d\n",player[i]->classe);
    }
    destroy_bitmap(pseudo);
    destroy_bitmap(choixclasse);
}


void menu_jeu(player_t *player[], game_t *game, spell_t ***spell,player_t *classe[]) {
    BITMAP *ecrantitre = load_bitmap("ecrantitre.bmp", NULL);
    BITMAP *menu = load_bitmap("menu.bmp", NULL);
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
            if (x >= 500 && x <= 1200 && y >= 100 && y <= 300) {
                configurerpartie(game);
                if (mouse_b & 1) {
                    classe_pseudos(game, player);
                    initplayer(player, game, spell,classe);
                    play(player, game, spell);
                }
            }

            else if (x >= 500 && x <= 1200 && y >= 400 && y <= 600) {
                quitter = 1;
                allegro_exit();
            }
        }
        rest(10);
    }
    destroy_bitmap(ecrantitre);
    destroy_bitmap(menu);
}

