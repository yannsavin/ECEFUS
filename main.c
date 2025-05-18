#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

volatile int temps_restant = 30;

void decrementer_timer() {
    if (temps_restant > 0)
        temps_restant--;
}

END_OF_FUNCTION(decrementer_timer);
LOCK_VARIABLE(temps_restant);
LOCK_FUNCTION(decrementer_timer);


int main() {
    game_t game;
    initialisation_allegro(&game);
    install_timer();
    install_int(decrementer_timer,1000);
    srand(time(NULL));
    game.tourjoueur=0;
    game.action=1;
    game.n_map = rand()%4;
    player_t *player[4];
    for (int i = 0; i < 4; i++) {
        player[i] = (player_t *)malloc(sizeof(player_t));
        if (!player[i]) {
            printf("Erreur d'allocation mémoire pour player[%d]\n", i);
            exit(EXIT_FAILURE);
        }
    }
    player_t *classe[4];
    for (int i = 0; i < 4; i++) {
        classe[i] = (player_t *)malloc(sizeof(player_t));
    }
    spell_t ***spell = (spell_t ***)malloc(4 * sizeof(spell_t **));
    for (int i = 0; i < 4; i++) {
        spell[i] = (spell_t **)malloc(4 * sizeof(spell_t *));
        for (int j = 0; j < 4; j++) {
            spell[i][j] = (spell_t*)malloc(sizeof(spell_t));
        }
    }
    printf("Avant init\n");
    init(player, &game, spell,classe);
    printf("Après init\n");
    printf("Avant init_map\n");
    init_map(&game);
    printf("Après init_map\n");
    printf("Avant affichage\n");
    menu_jeu(player, &game, spell,classe);
    printf("Après affichage\n");
    destroy(player,&game,spell);
    allegro_exit();
    return 0;
}
END_OF_MAIN()