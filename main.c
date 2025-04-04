#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"


#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 800
#define caseX 100
#define caseY 100
#define decalageX 350
#define decalageY 0
#define nbcases 8


BITMAP *buffer;
BITMAP *map;

void initialisation_allegro() {
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT); // Initialisation du buffer
    show_mouse(screen);
}

void init_map(game_t *game) {
    map = create_bitmap(800, 800);
    int map_data[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            map_data[i][j] = rand()%3;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            draw_sprite(map, game->cases[map_data[i][j]], i * caseX, j * caseY);
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
    player[0]->skin=load_bitmap("perso1.bmp",NULL);
    player[1]->skin=load_bitmap("perso2.bmp",NULL);
    player[2]->skin=load_bitmap("perso3.bmp",NULL);

    for(int i=0;i<3;i++) {
        player[i]->casex=rand()%nbcases;
        player[i]->casey=rand()%nbcases;
        player[i]->basePA=10;
        player[i]->PA=player[i]->basePA;
        player[i]->basePM=5;
        player[i]->PM=player[i]->basePM;
        player[i]->health=100;
        player[i]->state=1;
        player[i]->spellselect=-1;
        player[i]->damage=10;
        for (int j=0;j<3;j++) {player[i]->spelltab[j]=j;}

    }
}

int affichage(player_t *player[], game_t *game, spell_t *spell[]) {
    rest(50);
    clear_bitmap(buffer);
    blit(map, buffer, 0, 0, decalageX, 0, 800, 800);
    for (int i = 0; i < 3; i++) {
        if (player[i]->state==1) {
            player[i]->x = (player[i]->casex * caseX) + decalageX;
            player[i]->y = (player[i]->casey * caseY) + decalageY;
            draw_sprite(buffer, player[i]->skin, player[i]->x+10, player[i]->y+10);
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
                    draw_trans_sprite(buffer, create_bitmap(caseX, caseY), (nx * caseX) + decalageX, (ny * caseY) + decalageY);
                }
            }
        }
    }
    rectfill(buffer, 0, 0, 250, 800, makecol(0, 0, 0));
    draw_sprite(buffer, player[game->tourjoueur]->skin, 100, 0);

    textout_ex(buffer, font, "Tours de :", 10, 35, makecol(255, 255, 255), makecol(0, 0, 0));
    char buffer_text[10];
    sprintf(buffer_text, "%d", player[game->tourjoueur]->PM);
    textout_ex(buffer, font, buffer_text, 125, 130, makecol(255, 0, 0), makecol(0, 0, 0));
    sprintf(buffer_text, "%d", player[game->tourjoueur]->PA);
    textout_ex(buffer, font, buffer_text, 120, 150, makecol(0, 0, 255), makecol(0, 0, 0));
    sprintf(buffer_text, "%d", player[game->tourjoueur]->health);
    textout_ex(buffer, font, buffer_text, 115, 170, makecol(0, 255, 0), makecol(0, 0, 0));
    draw_sprite(buffer, spell[player[game->tourjoueur]->spelltab[0]]->skin, 85, 200);
    draw_sprite(buffer, spell[player[game->tourjoueur]->spelltab[1]]->skin, 85, 300);
    draw_sprite(buffer, spell[player[game->tourjoueur]->spelltab[2]]->skin, 85, 400);
    for (int i = 0; i < 3; i++) {
        if (player[i]->state==1) {
            draw_sprite(buffer, player[i]->skin, 1400, i*200);
            sprintf(buffer_text, "%d", player[i]->health);
            textout_ex(buffer, font, buffer_text, 1300, i*200+35, makecol(0, 255, 0), makecol(0, 0, 0));
        }
    }
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    rectfill(screen, 150, SCREEN_HEIGHT - 90, 230, SCREEN_HEIGHT - 10, makecol(0, 255, 0));
}
void skip(player_t *player[], game_t *game,spell_t *spell[]) {
    player[game->tourjoueur]->PA=player[game->tourjoueur]->basePA;
    player[game->tourjoueur]->PM=player[game->tourjoueur]->basePM;
    game->tourjoueur++;
    if (game->tourjoueur>=3) {
        game->tourjoueur=0;}
    while (player[game->tourjoueur]->state==0) {
        game->tourjoueur++;
        if (game->tourjoueur>=3) {
            game->tourjoueur=0;
        }

    }
    affichage(player,game,spell);
}
void next(player_t *player[], game_t *game, spell_t *spell[]) {
    if (150<=mouse_x && 230>=mouse_x && (SCREEN_HEIGHT - 90)<=mouse_y && mouse_y<=SCREEN_HEIGHT-10){
        if (mouse_b & 1) {
            skip(player,game,spell);
        }
    }
}


void moove(player_t *player[],game_t *game,spell_t *spell[]) {
    if (mouse_b & 1 && player[game->tourjoueur]->PM >0){
        int src_x = (mouse_x -decalageX)/caseX;
        int src_y = (mouse_y -decalageY)/caseY;
        if (mouse_x > decalageX && mouse_y > decalageY &&
        mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY &&
        src_x - player[game->tourjoueur]->casex >= -1 &&
        src_x - player[game->tourjoueur]->casex <= 1 &&
        src_y - player[game->tourjoueur]->casey >= -1 &&
        src_y - player[game->tourjoueur]->casey <= 1 &&
        (src_x!=(player[(game->tourjoueur+1)%3]->casex) ||
        src_y!=(player[(game->tourjoueur+1)%3]->casey)) &&
        (src_x!=(player[(game->tourjoueur+2)%3]->casex) ||
        src_y!=(player[(game->tourjoueur+2)%3]->casey))) {
            player[game->tourjoueur]->casex=src_x;
            player[game->tourjoueur]->casey=src_y;
            player[game->tourjoueur]->PM-=1;
            affichage(player,game,spell);
        }
        else if (mouse_x > decalageX && mouse_y > decalageY &&
        mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY &&
        src_x - player[game->tourjoueur]->casex >= -1 &&
        src_x - player[game->tourjoueur]->casex <= 1 &&
        src_y - player[game->tourjoueur]->casey >= -1 &&
        src_y - player[game->tourjoueur]->casey <= 1) {
            for (int i=0; i<3; i++) {
                if (src_x==player[i]->casex && src_y==player[i]->casey && player[game->tourjoueur]->PA>=2) {
                    player[i]->health-=player[game->tourjoueur]->damage;
                    player[game->tourjoueur]->PA-=2;
                    affichage(player,game,spell);
                }
            }
        }
    }
}
int life(player_t *player[],game_t *game,spell_t *spell[]) {
    for (int i = 0; i < 3; i++) {
        if(player[i]->health<=0) {
        player[i]->state=0;
        }
    }
}
int damagetaken(player_t *player[],game_t *game, spell_t *spell[],int src_y,int src_x) {
    for(int i=0;i<3;i++) {
        if(player[i]->casex==src_x && player[i]->casey==src_y) {
            player[i]->health-=spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->damage;
            life(player,&game,spell);
        }
    }
}
int sendspell(player_t *player[],game_t *game,spell_t *spell[],int src_y,int src_x) {
        for (int i=0;i<4;i++) {
            draw_sprite(screen, spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->frame[i], (src_x*caseX)+decalageX+(10*i), (src_y*caseY)+decalageY+(10*i));
            rest(100);
            affichage(player,game,spell);
        }
        damagetaken(player,game,spell,src_y,src_x);
        player[game->tourjoueur]->PA-=spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->PAcost;
        affichage(player,game,spell);
        return 1;
}

void place_spell(player_t *player[],game_t *game,spell_t *spell[]) {
    int a=0;
    while(a==0) {
        int src_x = (mouse_x -decalageX)/caseX;
        int src_y = (mouse_y -decalageY)/caseY;
        affichage(player,game,spell);
        if(mouse_x > decalageX && mouse_y > decalageY && mouse_x < (nbcases * caseX) + decalageX && mouse_y < (nbcases * caseY) + decalageY){
            //rectfill(screen, (src_x*caseX)+420,(src_y*caseY)+90,(src_x*caseX)+420+caseX ,(src_y*caseY)+90+caseY, makecol(255,0,0));
            set_trans_blender(255, 0, 0, 128);
            draw_trans_sprite(screen, create_bitmap(caseX, caseY), (src_x*caseX)+decalageX, (src_y*caseY)+decalageY);
            if (mouse_b & 1) {
                a=sendspell(player,game,spell,src_y,src_x);
            }
        }
        rest(100);
    }
}

void select_spell(player_t *player[],game_t *game,spell_t *spell[]) {
     if (mouse_b & 1) {
         if (85<=mouse_x && 165>=mouse_x && 200<=mouse_y && mouse_y<=280){
            player[game->tourjoueur]->spellselect=0;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->PAcost) {
                 place_spell(player,game,spell);
             }
             else {
                 player[game->tourjoueur]->spellselect=-1;
             }
        }
         if (85<=mouse_x && 165>=mouse_x && 300<=mouse_y && mouse_y<=380){
             player[game->tourjoueur]->spellselect=1;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->PAcost) {
                 place_spell(player,game,spell);
             }
             else {
                 player[game->tourjoueur]->spellselect=-1;
             }
         }
         if (85<=mouse_x && 165>=mouse_x && 400<=mouse_y && mouse_y<=480){
             player[game->tourjoueur]->spellselect=2;
             if (player[game->tourjoueur]->PA>=spell[player[game->tourjoueur]->spelltab[player[game->tourjoueur]->spellselect]]->PAcost) {
                 place_spell(player,game,spell);
             }
             else {
                 player[game->tourjoueur]->spellselect=-1;
             }
         }
    }
}
void destroy(player_t *player[],game_t *game,spell_t *spell[]) {
    for (int i = 0; i < game->nbplayers; i++) {
        free(player[i]);
    }
    destroy_bitmap(player[0]->skin);
}

int main() {
    initialisation_allegro();
    game_t game;
    srand(time(NULL));
    game.nbplayers=3;
    game.tourjoueur=0;
    game.action=1;
    player_t *player[game.nbplayers];
    for (int i = 0; i < game.nbplayers; i++) {
        player[i] = (player_t *)malloc(sizeof(player_t));
    }
    spell_t *spell[5];
    for (int i = 0; i < 5; i++) {
        spell[i] = (spell_t *)malloc(sizeof(spell_t));
    }
    init(player,&game,spell);
    init_map(&game);
    affichage(player,&game,spell);
    while (!key[KEY_ESC]) {
        moove(player,&game,spell);
        select_spell(player,&game,spell);
        rest(100);
        next(player,&game,spell);
    }
    destroy(player,&game,spell);
    allegro_exit();
    return 0;
}
END_OF_MAIN()
