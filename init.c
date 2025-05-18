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

void init_map(game_t *game, const char *nom_fichier) {
    game->map = create_bitmap(960, 960);

    if (game->n_map >= 0 && game->n_map <= 4) {
        FILE *f = fopen(nom_fichier, "r");
        if (!f) {
            perror("Erreur d'ouverture du fichier");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < nbcases; i++) {
            if (fscanf(f, "%d %d %d %d %d %d %d %d %d %d %d %d",
                       &game->data[i][0],
                       &game->data[i][1],
                       &game->data[i][2],
                       &game->data[i][3],
                       &game->data[i][4],
                       &game->data[i][5],
                       &game->data[i][6],
                       &game->data[i][7],
                       &game->data[i][8],
                       &game->data[i][9],
                       &game->data[i][10],
                       &game->data[i][11]) != 12){
                fprintf(stderr, "Erreur de lecture de la classe %d\n", i);
                fclose(f);
                exit(EXIT_FAILURE);
                       }
        }
        fclose(f);
    } else {
        game->n_map = rand()%4;
        for (int i = 0; i < nbcases; i++) {
            for (int j = 0; j < nbcases; j++) {
                int pourcentage = rand()%100;
                if (pourcentage < 75) {
                    game->data[i][j] = rand()%3;
                } else {
                    game->data[i][j] = rand()%3+2;
                }
            }
        }
    }
    for (int i = 0; i < nbcases; i++) {
        for (int j = 0; j < nbcases; j++) {
            draw_sprite(game->map, game->cases[game->n_map][game->data[i][j]], i * caseX, j * caseY);
        }
    }
}

void charger_classes(const char *nom_fichier, player_t *classe[]) {
    FILE *f = fopen(nom_fichier, "r");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 4; i++) {
        if (fscanf(f, "%d %d %d %d %d %d",
                   &classe[i]->basePA,
                   &classe[i]->basePM,
                   &classe[i]->health,
                   &classe[i]->damage,
                   &classe[i]->attaquecost,
                   &classe[i]->nb_skins) != 6){
            fprintf(stderr, "Erreur de lecture de la classe %d\n", i);
            fclose(f);
            exit(EXIT_FAILURE);
                   }
        for (int j = 0; j < classe[i]->nb_skins; j++) {
            char chemin[64];
            snprintf(chemin, sizeof(chemin), "image/perso%d.%d.bmp", i, j);
            classe[i]->skinclass[j] = load_bitmap(chemin, NULL);
            set_transparence(classe[i]->skinclass[j],0,0,0);
            if (!classe[i]->skinclass[j]) {
                fprintf(stderr, "Erreur chargement %s\n", chemin);
                exit(EXIT_FAILURE);
            }
            snprintf(chemin, sizeof(chemin), "image/affichage%d.%d.bmp", i, j);
            classe[i]->affichage[j] = load_bitmap(chemin, NULL);
            set_transparence(classe[i]->affichage[j],0,0,0);
            if (!classe[i]->affichage[j]) {
                fprintf(stderr, "Erreur chargement %s\n", chemin);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(f);
}

void charger_map(game_t *game) {
    for (int i=0; i<4; i++) {
        for (int j = 0; j < 5; j++) {
            char chemin[64];
            sprintf(chemin, "image/case%d.%d.bmp", i, j+1);
            game->cases[i][j] = load_bitmap(chemin, NULL);
            if (!game->cases[i][j]) {
                fprintf(stderr, "Erreur chargement %s\n", chemin);
                exit(EXIT_FAILURE);
            }
        }
    }
}
void charger_spell(const char *nom_fichier,spell_t ***spell) {
    FILE *f = fopen(nom_fichier, "r");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (fscanf(f, "%d %d %d %d %d %d %d",
                   &spell[i][j]->PAcost,
                   &spell[i][j]->damageMIN,
                   &spell[i][j]->damageMAX,
                   &spell[i][j]->miss,
                   &spell[i][j]->type,
                   &spell[i][j]->min,
                   &spell[i][j]->max) != 7){
                fprintf(stderr, "Erreur de lecture de la classe %d\n", i);
                fclose(f);
                exit(EXIT_FAILURE);
                   }
            char skin[64];
            snprintf(skin, sizeof(skin), "image/spell%d.%d.bmp", i, j);
            spell[i][j]->skin = load_bitmap(skin, NULL);
            set_transparence(spell[i][j]->skin,0,0,0);
            if (spell[i][j]->type==0) {
                for (int k = 0; k < 4; k++) {
                    char chemin[64];
                    snprintf(chemin, sizeof(chemin), "image/frame%d.%d.%d.bmp", i, j,k+1);
                    spell[i][j]->frame[k] = load_bitmap(chemin, NULL);
                    if (!spell[i][j]->frame[k]) {
                        fprintf(stderr, "Erreur chargement %s\n", chemin);
                        exit(EXIT_FAILURE);
                    }
                }
            }
            if (spell[i][j]->type==2) {
                char chemin[64];
                snprintf(chemin, sizeof(chemin), "image/frame%d.%d.%d.bmp", i, j,1);
                spell[i][j]->frame[0] = load_bitmap(chemin, NULL);
                set_transparence(spell[i][j]->frame[0],0,0,0);
                if (!spell[i][j]->frame[0]) {
                    fprintf(stderr, "Erreur chargement %s\n", chemin);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    fclose(f);
}

void init(player_t *player[],game_t *game, spell_t ***spell,player_t *classe[]) {
    game->conseille=-1;
    game->rank=0;

    charger_map(game);
    charger_spell("donees/spells.txt",spell);
    charger_classes("donees/classes.txt", classe);
    player[0]->skinnum=0;
    player[1]->skinnum=0;
    player[2]->skinnum=0;
    player[3]->skinnum=0;
}

void initplayer(player_t *player[],game_t *game, spell_t ***spell,player_t *classe[]) {
    int a,b;
    for(int i=0;i<game->nbplayers;i++) {
        player[i]->stackdamage=0;
        player[i]->incantation=0;
        player[i]->skin=classe[player[i]->classe]->skinclass[player[i]->skinnum];
        player[i]->casex=-1;
        player[i]->casey=-1;
        while (player[i]->casex==-1 || player[i]->casey==-1) {
            a=rand()%nbcases;
            b=rand()%nbcases;
            if (game->data[a][b]!=3 && game->data[a][b]!=4) {
                player[i]->casex=b;
                player[i]->casey=a;
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
        player[i]->basePA=classe[player[i]->classe]->basePA;
        player[i]->PA=player[i]->basePA;
        player[i]->basePM=classe[player[i]->classe]->basePM;
        player[i]->PM=player[i]->basePM;
        player[i]->basehealth=classe[player[i]->classe]->health;
        player[i]->health=player[i]->basehealth;
        player[i]->basedamage=classe[player[i]->classe]->damage;
        player[i]->damage=player[i]->basedamage;
        player[i]->attaquecost=classe[player[i]->classe]->attaquecost;
        player[i]->state=1;
        player[i]->spellselect=-1;
        player[i]->bonus=0;
        player[i]->stackDEMACIA=0;
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
