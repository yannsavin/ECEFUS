#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"



int main() {
    game_t game;
    initialisation_allegro(&game);
    srand(time(NULL));
    game.nbplayers=3;
    game.tourjoueur=0;
    game.action=1;
    player_t *player[game.nbplayers];
    for (int i = 0; i < game.nbplayers; i++) {
        player[i] = (player_t *)malloc(sizeof(player_t));
        if (!player[i]) {
            printf("Erreur d'allocation mémoire pour player[%d]\n", i);
            exit(EXIT_FAILURE);
        }
    }
    spell_t ***spell = (spell_t ***)malloc(4 * sizeof(spell_t **));
    for (int i = 0; i < 4; i++) {
        spell[i] = (spell_t **)malloc(4 * sizeof(spell_t *));
        for (int j = 0; j < 4; j++) {
            spell[i][j] = (spell_t *)malloc(sizeof(spell_t));
        }
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