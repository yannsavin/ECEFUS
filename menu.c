#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "game.h"

//partie menu


void play(player_t *player[], game_t *game, spell_t ***spell,player_t *classe[]){
    affichage(player, game, spell);
    while (!key[KEY_ESC]) {
        moove(player,game,spell);
        select_spell(player,game,spell);
        life(player,game);
        temps(player,game,spell);
        affichage(player,game,spell);
        rest(50);
        fin(player,game,spell,classe);
        next(player,game,spell);
    }
}

void reinit_player(player_t *player[], game_t *game, spell_t ***spell, player_t *classe[]){
    int a,b;
    for(int i=0;i<game->nbplayers;i++) {
        player[i]->stackdamage = 0;
        player[i]->incantation = 0;
        player[i]->casex=-1;
        player[i]->casey=-1;
        while (player[i]->casex==-1 || player[i]->casey==-1) {
            a=rand()%nbcases;
            b=rand()%nbcases;
            if (game->data[a][b]!=3 && game->data[a][b]!=4) {
                player[i]->casex=a;
                player[i]->casey=b;
            }
        }
        player[i]->pixel_x = player[i]->casex * caseX + decalageX;
        player[i]->pixel_y = player[i]->casey * caseY + decalageY;
        player[i]->stund=0;
        player[i]->ccimune=0;
        player[i]->stack=0;
        player[i]->shild=0;
        player[i]->dodge=0;
        player[i]->action=0;
        player[i]->healcd=0;
        player[i]->cleanscd=0;
        player[i]->state=1;
        player[i]->spellselect=-1;
        player[i]->health=player[i]->basehealth;
    }
}

void choixmap(player_t *player[], game_t *game, spell_t ***spell, player_t *classe[]) {
    BITMAP *choixcarte = load_bitmap("image/choix map.bmp", NULL);
    stretch_blit(choixcarte, screen, 0, 0, choixcarte->w, choixcarte->h, 0, 0, SCREEN_W, SCREEN_H);
    int choisi = 0;
    while (!choisi) {
        if (mouse_b & 1) {
            int x = mouse_x;
            int y = mouse_y;
            if (x >= 83 && x <= 355 && y >= 500 && y <= 790) {
                game->n_map=2;
                init_map(player,game,spell,classe, "donees/montagne.txt");
                choisi=1;
            } else if (x >= 400 && x <= 670 && y >= 500 && y <= 790) {
                game->n_map=1;
                init_map(player,game,spell,classe, "donees/neige.txt");
                choisi=1;
            } else if (x >= 715 && x <= 985 && y >= 500 && y <= 790) {
                game->n_map=3;
                init_map(player,game,spell,classe, "donees/sable.txt");
                choisi=1;
            } else if (x >= 1030 && x <= 1285 && y >= 500 && y <= 790) {
                game->n_map=0;
                init_map(player,game,spell,classe, "donees/foret.txt");
                choisi=1;
            } else if (x >= 1325 && x <= 1600 && y >= 500 && y <= 790) {
                game->n_map = 5;
                init_map(player,game,spell,classe, "donees/foret.txt");
                choisi=1;
            }
            rest(10);
        }
    }
    destroy_bitmap(choixcarte);
}
void afficher_classement(player_t *player[], game_t *game) {
    clear_to_color(screen, makecol(0, 0, 0));
    BITMAP *classement = load_bitmap("image/classement.bmp", NULL);
    stretch_blit(classement, screen, 0, 0, classement->w, classement->h, 0, 0, SCREEN_W, SCREEN_H);
    textout_ex(screen, font, "Classement :", 700, 400, makecol(255, 255, 255), -1);

    const int start_y = 450;
    const int line_spacing = 30;

    for (int r = 0; r <= game->nbplayers; r++) {
        printf("\n%d ",r);
        for (int i = 0; i < game->nbplayers; i++) {
            printf(" %d ",i);
            if (player[i]->rang == r) {
                printf("gg");
                char buffer[64];
                sprintf(buffer, "%d. %s", r, player[i]->name);
                textout_ex(screen, font, buffer, 700, start_y + (r - 1) * line_spacing, makecol(255, 255, 255), -1);
                break;
            }
        }
    }

    while (!(mouse_b & 1)) rest(10);
    while (mouse_b & 1) rest(10);
}


void fin(player_t *player[], game_t *game, spell_t ***spell, player_t *classe[]) {
    int a=0;
    BITMAP *ecranapres = load_bitmap("image/ecran fin.bmp", NULL);
    for (int i=0; i< game->nbplayers; i++) {
        if (player[i]->state==0) {
            a+=1;
        }
    }
    if (a==game->nbplayers-1) {
        for (int i = 0; i < game->nbplayers; i++) {
            if (player[i]->state == 1 && player[i]->rang == 0) {
                player[i]->rang = game->rank;
            }
        }
        afficher_classement(player, game);
        stretch_blit(ecranapres, screen, 0, 0, ecranapres->w, ecranapres->h, 0, 0, SCREEN_W, SCREEN_H);
        int choisi = 0;
        while (!choisi) {
            if (mouse_b & 1) {
                int x = mouse_x;
                int y = mouse_y;
                while (mouse_b & 1) {
                    rest(10);
                }
                if (x >= 420 && x <= 1100 && y >= 380 && y <= 500) {
                    reinit_player(player,game,spell,classe);
                    temps_restant = 30;
                    play(player, game, spell, classe);
                }
                else if(x >= 420 && x <= 1100 && y >= 580 && y <= 700){
                    configurerpartie(game);
                    rest(100);
                    classe_pseudos(game, player,classe);
                    initplayer(player, game, spell, classe);
                    choixmap(player,game,spell,classe);
                    temps_restant = 30;
                    play(player, game, spell, classe);
                }
                else if (x >= 420 && x <= 1100 && y >= 770 && y <= 900) {
                    choisi = 1;
                    allegro_exit();
                }
            }
        }
    }
    destroy_bitmap(ecranapres);
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


void classe_pseudos(game_t *game, player_t *player[],player_t *classe[]){
    BITMAP *pseudo = load_bitmap("image/saisi pseudo.bmp", NULL);
    BITMAP *choixclasse = load_bitmap("image/choix class.bmp", NULL);
    BITMAP *choixskin = load_bitmap("image/choix skin.bmp", NULL);
    stretch_blit(pseudo, screen, 0, 0, pseudo->w, pseudo->h, 0, 0, SCREEN_W, SCREEN_H);
    for(int i=0; i<game->nbplayers; i++) {
        char saisie[10] = "";
        int pos=0;
        while (1) {
            stretch_blit(pseudo, screen, 0, 0, pseudo->w, pseudo->h, 0, 0, SCREEN_W, SCREEN_H);
            textprintf_centre_ex(screen, font, 750, 700, makecol(255, 255, 255), -1, "%s", saisie);
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
                if (x >= 115 && x <= 420 && y >= 310 && y <= 925) {
                    player[i]->classe = guerrier;
                    choisi = 1;
                } else if (x >= 465 && x <= 775 && y >= 310 && y <= 925) {
                    player[i]->classe = mage;
                    choisi = 1;
                } else if (x >= 820 && x <= 1130 && y >= 310 && y <= 925) {
                    player[i]->classe = assasin;
                    choisi = 1;
                } else if (x >= 1175 && x <= 1490 && y >= 310 && y <= 925) {
                    player[i]->classe = paladin;
                    choisi = 1;
                }
                while(mouse_b & 1) { rest(10); }
            }
        }
        stretch_blit(choixskin, screen, 0, 0, choixclasse->w, choixclasse->h, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite(screen, classe[player[i]->classe]->affichage[0], 400,500);
        draw_sprite(screen, classe[player[i]->classe]->affichage[1], 800,500);
        int choisie = 0;
        while (!choisie) {
            if (mouse_b & 1) {
                int x = mouse_x;
                int y = mouse_y;
                if (x >= 400 && x <= 700 && y >= 500 && y <= 800) {
                    player[i]->skinnum = 0;
                    choisie = 1;
                } else if (x >= 800 && x <= 1100 && y >= 500 && y <= 800) {
                    player[i]->skinnum = 1;
                    choisie = 1;
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
                game->rank=game->nbplayers;
                rest(100);
                classe_pseudos(game, player,classe);
                initplayer(player, game, spell,classe);
                choixmap(player,game,spell,classe);
                temps_restant=30;
                play(player, game, spell,classe);
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

