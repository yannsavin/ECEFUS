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
    game->map = create_bitmap(800, 800);
    int map_data[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int pourcentage = rand() % 100;
            if (pourcentage < 70) {
                map_data[i][j] = rand()%3;
            } else {
                map_data[i][j] = rand()%3+2;
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            game->data[i][j]=map_data[i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            draw_sprite(game->map, game->cases[n_map][map_data[i][j]], i * caseX, j * caseY);
        }
    }
}
void init(player_t *player[],game_t *game, spell_t ***spell) {
    int a,b;
    game->conseille=-1;
    player_t classe[4];
    game->cases[0][0]=load_bitmap("foret1.bmp",NULL);
    game->cases[0][1]=load_bitmap("foret2.bmp",NULL);
    game->cases[0][2]=load_bitmap("foret3.bmp",NULL);
    game->cases[0][3]=load_bitmap("foret4.bmp",NULL);
    game->cases[0][4]=load_bitmap("foret5.bmp",NULL);
    game->cases[1][0]=load_bitmap("sable1.bmp",NULL);
    game->cases[1][1]=load_bitmap("sable2.bmp",NULL);
    game->cases[1][2]=load_bitmap("sable3.bmp",NULL);
    game->cases[1][3]=load_bitmap("sable4.bmp",NULL);
    game->cases[1][4]=load_bitmap("sable5.bmp",NULL);
    game->cases[2][0]=load_bitmap("montagne1.bmp",NULL);
    game->cases[2][1]=load_bitmap("montagne2.bmp",NULL);
    game->cases[2][2]=load_bitmap("montagne3.bmp",NULL);
    game->cases[2][3]=load_bitmap("montagne4.bmp",NULL);
    game->cases[2][4]=load_bitmap("montagne5.bmp",NULL);
    game->cases[3][0]=load_bitmap("neige1.bmp",NULL);
    game->cases[3][1]=load_bitmap("neige2.bmp",NULL);
    game->cases[3][2]=load_bitmap("neige3.bmp",NULL);
    game->cases[3][3]=load_bitmap("neige4.bmp",NULL);
    game->cases[3][4]=load_bitmap("neige5.bmp",NULL);

    //mage
    classe[0].skinclass[0]=load_bitmap("perso_mage.bmp",NULL);
    classe[0].skinclass[1]=load_bitmap("perso_mage1.bmp",NULL);
    classe[0].skinclass[2]=load_bitmap("perso_mage2.bmp",NULL);
    classe[0].basePA=14;
    classe[0].basePM=4;
    classe[0].health=100;
    classe[0].damage=5;
    classe[0].attaquecost=3;

    spell[0][0]->PAcost=3;
    spell[0][0]->damageMIN=10;
    spell[0][0]->damageMAX=35;
    spell[0][0]->miss=15;
    spell[0][0]->type=0;
    spell[0][0]->min=1;
    spell[0][0]->max=4;
    spell[0][0]->skin=load_bitmap("spell_0_0.bmp",NULL);
    spell[0][0]->frame[0]=load_bitmap("eau1.bmp",NULL);
    spell[0][0]->frame[1]=load_bitmap("eau2.bmp",NULL);
    spell[0][0]->frame[2]=load_bitmap("eau3.bmp",NULL);
    spell[0][0]->frame[3]=load_bitmap("eau4.bmp",NULL);

    spell[0][1]->PAcost=5;
    spell[0][1]->damageMIN=30;
    spell[0][1]->damageMAX=55;
    spell[0][1]->miss=15;
    spell[0][1]->type=0;
    spell[0][1]->min=1;
    spell[0][1]->max=4;
    spell[0][1]->skin=load_bitmap("spell_0_1.bmp",NULL);
    spell[0][1]->frame[0]=load_bitmap("feu1.bmp",NULL);
    spell[0][1]->frame[1]=load_bitmap("feu2.bmp",NULL);
    spell[0][1]->frame[2]=load_bitmap("feu3.bmp",NULL);
    spell[0][1]->frame[3]=load_bitmap("feu4.bmp",NULL);

    spell[0][2]->PAcost=7;
    spell[0][2]->damageMIN=60;
    spell[0][2]->damageMAX=80;
    spell[0][2]->miss=20;
    spell[0][2]->type=0;
    spell[0][2]->min=1;
    spell[0][2]->max=4;
    spell[0][2]->skin=load_bitmap("spell_0_2.bmp",NULL);
    spell[0][2]->frame[0]=load_bitmap("foudre1.bmp",NULL);
    spell[0][2]->frame[1]=load_bitmap("foudre2.bmp",NULL);
    spell[0][2]->frame[2]=load_bitmap("foudre3.bmp",NULL);
    spell[0][2]->frame[3]=load_bitmap("foudre4.bmp",NULL);

    //guerrier
    classe[1].skinclass[0]=load_bitmap("perso_guerrier.bmp",NULL);
    classe[1].skinclass[1]=load_bitmap("perso_guerrier1.bmp",NULL);
    classe[1].skinclass[2]=load_bitmap("perso_guerrier2.bmp",NULL);
    classe[1].skinclass[3]=load_bitmap("perso_guerrier3.bmp",NULL);
    classe[1].skinclass[4]=load_bitmap("perso_guerrier4.bmp",NULL);
    classe[1].basePA=10;
    classe[1].basePM=6;
    classe[1].health=130;
    classe[1].damage=15;
    classe[1].attaquecost=2;

    spell[1][0]->skin=load_bitmap("spell1.0.bmp",NULL);
    spell[1][0]->frame[0]=load_bitmap("foudre1.bmp",NULL);
    spell[1][0]->frame[1]=load_bitmap("foudre2.bmp",NULL);
    spell[1][0]->frame[2]=load_bitmap("foudre3.bmp",NULL);
    spell[1][0]->frame[3]=load_bitmap("foudre4.bmp",NULL);
    spell[1][0]->PAcost=2;
    spell[1][0]->damageMIN=10;
    spell[1][0]->damageMAX=25;
    spell[1][0]->miss=10;
    spell[1][0]->type=0;
    spell[1][0]->min=1;
    spell[1][0]->max=4;

    spell[1][1]->skin=load_bitmap("spell1.1.bmp",NULL);
    spell[1][1]->PAcost=2;
    spell[1][1]->type=1;
    spell[1][1]->damageMIN=0;
    spell[1][1]->damageMAX=0;
    spell[1][1]->miss=0;
    spell[1][1]->min=1;
    spell[1][1]->max=4;

    spell[1][2]->skin=load_bitmap("spell1.2.bmp",NULL);
    spell[1][2]->PAcost=3;
    spell[1][2]->type=1;
    spell[1][2]->damageMIN=0;
    spell[1][2]->damageMAX=0;
    spell[1][2]->miss=0;
    spell[1][2]->min=1;
    spell[1][2]->max=4;

    //assasin
    classe[2].skinclass[0]=load_bitmap("perso_assasin.bmp",NULL);
    classe[2].skinclass[1]=load_bitmap("perso_assasin1.bmp",NULL);
    classe[2].skinclass[2]=load_bitmap("perso_assasin2.bmp",NULL);
    classe[2].basePA=10;
    classe[2].basePM=6;
    classe[2].health=110;
    classe[2].damage=20;
    classe[2].attaquecost=2;

    spell[2][0]->skin=load_bitmap("spell2.0.bmp",NULL);
    spell[2][0]->PAcost=4;
    spell[2][0]->damageMIN=10;
    spell[2][0]->damageMAX=20;
    spell[2][0]->miss=10;
    spell[2][0]->type=0;
    spell[2][0]->min=1;
    spell[2][0]->max=4;

    spell[2][1]->skin=load_bitmap("spell2.1.bmp",NULL);
    spell[2][1]->PAcost=2;
    spell[2][1]->type=1;
    spell[2][1]->damageMIN=0;
    spell[2][1]->damageMAX=0;
    spell[2][1]->miss=0;
    spell[2][1]->min=1;
    spell[2][1]->max=4;

    spell[2][2]->skin=load_bitmap("spell2.2.bmp",NULL);
    spell[2][2]->PAcost=3;
    spell[2][2]->type=1;
    spell[2][2]->damageMIN=0;
    spell[2][2]->damageMAX=0;
    spell[2][2]->miss=0;
    spell[2][2]->min=1;
    spell[2][2]->max=4;

    //paladin
    classe[3].skinclass[0]=load_bitmap("perso_paladin.bmp",NULL);
    classe[3].skinclass[1]=load_bitmap("perso_paladin1.bmp",NULL);
    classe[3].skinclass[2]=load_bitmap("perso_paladin2.bmp",NULL);
    classe[3].basePA=10;
    classe[3].basePM=6;
    classe[3].health=110;
    classe[3].damage=20;
    classe[3].attaquecost=2;

    spell[3][0]->skin=load_bitmap("spell3.0.bmp",NULL);
    spell[3][0]->PAcost=2;
    spell[3][0]->damageMIN=10;
    spell[3][0]->damageMAX=20;
    spell[3][0]->miss=10;
    spell[3][0]->type=1;
    spell[3][0]->min=1;
    spell[3][0]->max=4;

    spell[3][1]->skin=load_bitmap("spell3.1.bmp",NULL);
    spell[3][1]->PAcost=2;
    spell[3][1]->type=1;
    spell[3][1]->damageMIN=0;
    spell[3][1]->damageMAX=0;
    spell[3][1]->miss=0;
    spell[3][1]->min=1;
    spell[3][1]->max=4;

    spell[3][2]->skin=load_bitmap("spell3.1.bmp",NULL);
    spell[3][2]->PAcost=3;
    spell[3][2]->type=1;
    spell[3][2]->damageMIN=0;
    spell[3][2]->damageMAX=0;
    spell[3][2]->miss=0;
    spell[3][2]->min=1;
    spell[3][2]->max=4;


    player[0]->classe=0;
    player[0]->skinnum=0;
    player[1]->classe=0;
    player[1]->skinnum=1;
    player[2]->classe=0;
    player[2]->skinnum=2;
    for(int i=0;i<3;i++) {
        player[i]->stackdamage=0;
        player[i]->skin=classe[player[i]->classe].skinclass[player[i]->skinnum];
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

void destroy(player_t *player[],game_t *game,spell_t ***spell) {
    for (int i = 0; i < game->nbplayers; i++) {
        destroy_bitmap(player[i]->skin);
    }
    for (int i = 0; i < game->nbplayers; i++) {
        free(player[i]);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            free(spell[i][j]);
        }
        free(spell[i]);
    }
    free(spell);
}
