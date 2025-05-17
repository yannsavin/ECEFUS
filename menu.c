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
        rest(100);
        next(player,game,spell);
    }
}

void configurerpartie(game_t *game){
    BITMAP *nbjoueurs = load_bitmap("nbjoueurs.bmp", NULL);
    BITMAP *pseudo = load_bitmap("pseudo.bmp", NULL);
    BITMAP *choixclasse = load_bitmap("choixclasse.bmp", NULL);
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
        /*stretch_blit(pseudo, screen, 0, 0, pseudo->w, pseudo->h, 0, 0, SCREEN_W, SCREEN_H);

        if (game.nbplayers=2){
            do {
                scanf("%s", &j2->name);
            } while (strlen(j2.name) <= 0 && strlen(j2->name) > 10);
        }
        if (game.nbplayers=3){
            do {
                scanf("%s", &j3->nom);
            } while (strlen(j3->name) <= 0 && strlen(j3->nom) > 10);

        }
        if (game.nbplayers=4) {
            do {
                scanf("%s", &j4->nom);
            } while (strlen(j4->nom) <= 0 && strlen(j4->nom) > 10);
        }


    for(int i=0; i<game.nbplayers; i++){
        stretch_blit(choixclasse, screen,0, 0, choixclasse->w, choixclasse->h, 0, 0, SCREEN_W, SCREEN_H);
        if(mouse_b &1) {
            int x = mouse_x;
            int y = mouse_y;
            if (x >= 100 && x <= 200 && y >= 300 && y <= 400) {
                player.classe = 1;
            } else if (x >= 400 && x <= 500 && y >= 300 && y <= 400) {
                player.classe = 2;
            } else if (x >= 700 && x <= 800 && y >= 300 && y <= 400) {
                player.classe = 3;
            } else if (x >= 1000 && x <= 1100 && y >= 300 && y <= 400) {
                player.classe = 4;
            }

        }
    }
    destroy_bitmap(nbjoueurs);
    destroy_bitmap(pseudo);
    destroy_bitmap(choixclasse);    */

}


void menu_jeu(player_t *player[], game_t *game, spell_t ***spell,player_t *classe[]) {
    BITMAP *ecrantitre = load_bitmap("ecrantitre.bmp", NULL);
    BITMAP *menu = load_bitmap("menu.bmp", NULL);
    BITMAP *ecranapres = load_bitmap("ecranapres.bmp", NULL);
    stretch_blit(ecrantitre, screen,0, 0, ecrantitre->w, ecrantitre->h, 0, 0, SCREEN_W, SCREEN_H);
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
                initplayer(player, game, spell,classe);
                if (mouse_b & 1) {
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

