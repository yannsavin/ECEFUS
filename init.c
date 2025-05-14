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
void init(player_t *player[],game_t *game, spell_t **spell) {
    game->conseille=-1;
    player_t classe[4];
    game->cases[0]=load_bitmap("carre0.bmp",NULL);
    game->cases[1]=load_bitmap("carre1.bmp",NULL);
    game->cases[2]=load_bitmap("carre2.bmp",NULL);

    //mage
    classe[0].skin=load_bitmap("perso_mage.bmp",NULL);
    classe[0].basePA=14;
    classe[0].basePM=4;
    classe[0].health=100;
    classe[0].damage=5;
    classe[0].attaquecost=3;

    spell[0][0].PAcost=3;
    spell[0][0].damage=30;
    spell[0][0].type=0;
    spell[0][0].min=1;
    spell[0][0].max=4;
    spell[0][0].skin=load_bitmap("spell_0_0.bmp",NULL);
    spell[0][0].frame[0]=load_bitmap("eau1.bmp",NULL);
    spell[0][0].frame[1]=load_bitmap("eau2.bmp",NULL);
    spell[0][0].frame[2]=load_bitmap("eau3.bmp",NULL);
    spell[0][0].frame[3]=load_bitmap("eau4.bmp",NULL);

    spell[0][1].PAcost=5;
    spell[0][1].damage=50;
    spell[0][1].type=0;
    spell[0][1].min=1;
    spell[0][1].max=4;
    spell[0][1].skin=load_bitmap("spell_0_1.bmp",NULL);
    spell[0][1].frame[0]=load_bitmap("feu1.bmp",NULL);
    spell[0][1].frame[1]=load_bitmap("feu2.bmp",NULL);
    spell[0][1].frame[2]=load_bitmap("feu3.bmp",NULL);
    spell[0][1].frame[3]=load_bitmap("feu4.bmp",NULL);

    spell[0][2].PAcost=7;
    spell[0][2].damage=70;
    spell[0][2].type=0;
    spell[0][2].min=1;
    spell[0][2].max=4;
    spell[0][2].skin=load_bitmap("spell_0_2.bmp",NULL);
    spell[0][2].frame[0]=load_bitmap("foudre1.bmp",NULL);
    spell[0][2].frame[1]=load_bitmap("foudre2.bmp",NULL);
    spell[0][2].frame[2]=load_bitmap("foudre3.bmp",NULL);
    spell[0][2].frame[3]=load_bitmap("foudre4.bmp",NULL);

    //guerrier
    classe[1].skin=load_bitmap("perso_guerrier1.bmp",NULL);
    classe[1].basePA=10;
    classe[1].basePM=6;
    classe[1].health=130;
    classe[1].damage=15;
    classe[1].attaquecost=2;

    spell[1][0].skin=load_bitmap("spell1.0.bmp",NULL);
    spell[1][0].frame[0]=load_bitmap("foudre1.bmp",NULL);
    spell[1][0].frame[1]=load_bitmap("foudre2.bmp",NULL);
    spell[1][0].frame[2]=load_bitmap("foudre3.bmp",NULL);
    spell[1][0].frame[3]=load_bitmap("foudre4.bmp",NULL);
    spell[1][0].PAcost=2;
    spell[1][0].damage=20;
    spell[1][0].type=0;
    spell[1][0].min=1;
    spell[1][0].max=4;

    spell[1][1].skin=load_bitmap("spell1.1.bmp",NULL);
    spell[1][1].PAcost=2;
    spell[1][1].type=1;
    spell[1][1].damage=0;
    spell[1][1].min=1;
    spell[1][1].max=4;

    spell[1][2].skin=load_bitmap("spell1.2.bmp",NULL);
    spell[1][2].PAcost=3;
    spell[1][2].type=1;
    spell[1][2].damage=0;
    spell[1][2].min=1;
    spell[1][2].max=4;

    //assasin
    classe[2].skin=load_bitmap("perso_assasin.bmp",NULL);
    classe[2].basePA=10;
    classe[2].basePM=6;
    classe[2].health=110;
    classe[2].damage=20;
    classe[2].attaquecost=2;

    spell[2][0].skin=load_bitmap("spell2.0.bmp",NULL);
    spell[2][0].PAcost=2;
    spell[2][0].damage=20;
    spell[2][0].type=1;
    spell[2][0].min=1;
    spell[2][0].max=4;

    spell[2][1].skin=load_bitmap("spell2.1.bmp",NULL);
    spell[2][1].PAcost=2;
    spell[2][1].type=1;
    spell[2][1].damage=0;
    spell[2][1].min=1;
    spell[2][1].max=4;

    spell[2][2].skin=load_bitmap("spell2.2.bmp",NULL);
    spell[2][2].PAcost=3;
    spell[2][2].type=1;
    spell[2][2].damage=0;
    spell[2][2].min=1;
    spell[2][2].max=4;

    //paladin
    classe[3].skin=load_bitmap("perso3.bmp",NULL);
    classe[3].basePA=10;
    classe[3].basePM=6;
    classe[3].health=110;
    classe[3].damage=20;
    classe[3].attaquecost=2;

    player[0]->classe=0;
    player[1]->classe=1;
    player[2]->classe=2;
    for(int i=0;i<3;i++) {
        player[i]->stackdamage=0;
        player[i]->skin=classe[player[i]->classe].skin;
        player[i]->casex=rand()%nbcases;
        player[i]->casey=rand()%nbcases;
        player[i]->basePA=classe[player[i]->classe].basePA;
        player[i]->PA=player[i]->basePA;
        player[i]->basePM=classe[player[i]->classe].basePM;
        player[i]->PM=player[i]->basePM;
        player[i]->basehealth=classe[player[i]->classe].health;
        player[i]->health=player[i]->basehealth;
        player[i]->basedamage=classe[player[i]->classe].damage;
        player[i]->damage=player[i]->basedamage;
        player[i]->attaquecost=classe[player[i]->classe].attaquecost;
        player[i]->state=1;
        player[i]->spellselect=-1;
        player[i]->bonus=0;
        for (int j=0;j<3;j++) {player[i]->spelltab[j]=j;}
    }
}

void destroy(player_t *player[],game_t *game,spell_t **spell) {
    for (int i = 0; i < game->nbplayers; i++) {
        free(player[i]);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            free(&spell[i][j]);
        }
    }
    destroy_bitmap(player[0]->skin);
}
