#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"


void initialisation_allegro(game_t *game) {
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    game->buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT); // Initialisation du game->buffer
    show_mouse(screen);
}

void init_map(game_t *game) {
    BITMAP *map;
    game->map = create_bitmap(800, 800);
    int map_data[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            map_data[i][j] = rand()%3;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            draw_sprite(game->map, game->cases[map_data[i][j]], i * caseX, j * caseY);
        }
    }
}
void init(player_t *player[],game_t *game, spell_t *spell[]) {
    spell[0]->PAcost=3;
    spell[0]->damage=30;
    spell[1]->PAcost=5;
    spell[1]->damage=50;
    spell[2]->PAcost=7;
    spell[2]->damage=70;
    spell[0]->skin=load_bitmap("eau_visu.bmp",NULL);
    spell[0]->frame[0]=load_bitmap("eau1.bmp",NULL);
    spell[0]->frame[1]=load_bitmap("eau2.bmp",NULL);
    spell[0]->frame[2]=load_bitmap("eau3.bmp",NULL);
    spell[0]->frame[3]=load_bitmap("eau4.bmp",NULL);
    spell[1]->skin=load_bitmap("feu_visu.bmp",NULL);
    spell[1]->frame[0]=load_bitmap("feu1.bmp",NULL);
    spell[1]->frame[1]=load_bitmap("feu2.bmp",NULL);
    spell[1]->frame[2]=load_bitmap("feu3.bmp",NULL);
    spell[1]->frame[3]=load_bitmap("feu4.bmp",NULL);
    spell[2]->skin=load_bitmap("foudre_visu.bmp",NULL);
    spell[2]->frame[0]=load_bitmap("foudre1.bmp",NULL);
    spell[2]->frame[1]=load_bitmap("foudre2.bmp",NULL);
    spell[2]->frame[2]=load_bitmap("foudre3.bmp",NULL);
    spell[2]->frame[3]=load_bitmap("foudre4.bmp",NULL);
    game->cases[0]=load_bitmap("carre0.bmp",NULL);
    game->cases[1]=load_bitmap("carre1.bmp",NULL);
    game->cases[2]=load_bitmap("carre2.bmp",NULL);

    player_t classe[4];
    //mage
    classe[0].skin=load_bitmap("perso1.bmp",NULL);
    classe[0].basePA=10;
    classe[0].basePM=4;
    classe[0].health=100;
    classe[0].damage=5;
    classe[0].attaquecost=3;

    //guerrier
    classe[1].skin=load_bitmap("perso2.bmp",NULL);
    classe[1].basePA=7;
    classe[1].basePM=6;
    classe[1].health=130;
    classe[1].damage=10;
    classe[1].attaquecost=2;

    //assasin
    classe[2].skin=load_bitmap("perso3.bmp",NULL);
    classe[2].basePA=7;
    classe[2].basePM=6;
    classe[2].health=110;
    classe[2].damage=15;
    classe[2].attaquecost=2;

    player[0]->classe=0;
    player[1]->classe=1;
    player[2]->classe=2;
    for(int i=0;i<3;i++) {
        player[i]->skin=classe[player[i]->classe].skin;
        player[i]->casex=rand()%nbcases;
        player[i]->casey=rand()%nbcases;
        player[i]->basePA=classe[player[i]->classe].basePA;
        player[i]->PA=player[i]->basePA;
        player[i]->basePM=classe[player[i]->classe].basePM;
        player[i]->PM=player[i]->basePM;
        player[i]->health=classe[player[i]->classe].health;
        player[i]->attaquecost=classe[player[i]->classe].attaquecost;
        player[i]->state=1;
        player[i]->spellselect=-1;
        player[i]->damage=classe[player[i]->classe].damage;
        for (int j=0;j<3;j++) {player[i]->spelltab[j]=j;}
    }
}

void destroy(player_t *player[],game_t *game,spell_t *spell[]) {
    for (int i = 0; i < game->nbplayers; i++) {
        free(player[i]);
    }
    destroy_bitmap(player[0]->skin);
}
