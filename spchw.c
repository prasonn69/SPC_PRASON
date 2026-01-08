#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT 100

typedef struct {
    int current_room;
    int health;
    int has_key;
    int has_sword;
    int has_torch;
    int monster_alive; // Added: To track if the monster is still there
    int game_over;
    int won;
} GameState;

void init_game(GameState *state) {
    state->current_room = 0;
    state->health = 100;
    state->has_key = 0;
    state->has_sword = 0;
    state->has_torch = 0;
    state->monster_alive = 1; // Monster starts alive
    state->game_over = 0;
    state->won = 0;
    srand(time(NULL));
}

void print_status(GameState *game) {
    printf("\n--- STATUS REPORT ---\n");
    printf("Health: [%d/100]\n", game->health);
    printf("Items: ");
    int empty = 1;
    if (game->has_key) { printf("[Key] "); empty = 0; }
    if (game->has_sword) { printf("[Sword] "); empty = 0; }
    if (game->has_torch) { printf("[Torch] "); empty = 0; }
    if (empty) printf("None");
    printf("\n---------------------\n");
}



void describe_room(int room) {
    switch(room) {
        case 0:
            printf("\n=== ENTRANCE HALL ===\n");
            printf("You are in a damp hall. Wooden door (NORTH), stone arch (EAST).\n");
            break;
        case 1:
            printf("\n=== ARMORY ===\n");
            printf("Rusted gear everywhere. A SHINING SWORD sits on a pedestal.\n");
            printf("Exits: SOUTH, EAST.\n");
            break;
        case 2:
            printf("\n=== LIBRARY ===\n");
            printf("Dusty books line the walls. A flickering TORCH is mounted here.\n");
            printf("Exits: WEST, NORTH.\n");
            break;
        case 3:
            printf("\n=== TREASURE ROOM ===\n");
            printf("Glittering gold! A massive locked CHEST is in the center.\n");
            printf("Exits: WEST, SOUTH.\n");
            break;
        case 4:
            printf("\n=== DARK CORRIDOR ===\n");
            printf("It's freezing. You hear growling to the NORTH.\n");
            printf("Exits: NORTH, WEST, SOUTH.\n");
            break;
        case 5:
            printf("\n=== MONSTER DEN ===\n");
            if (1) { // Logic handled in the room function
                printf("A massive beast snarls at you!\n");
            }
            printf("Exits: SOUTH.\n");
            break;
    }
}

// Room functions (Simplified and Fixed)
void room_entrance(GameState *state, char *input) {
    if (strcmp(input, "n") == 0 || strcmp(input, "north") == 0) state->current_room = 4;
    else if (strcmp(input, "e") == 0 || strcmp(input, "east") == 0) state->current_room = 1;
    else printf("You can't go that way.\n");
}

void room_armory(GameState *state, char *input) {
    if (strcmp(input, "s") == 0 || strcmp(input, "south") == 0) state->current_room = 0;
    else if (strcmp(input, "e") == 0 || strcmp(input, "east") == 0) state->current_room = 2;
    else if (strstr(input, "sword")) {
        state->has_sword = 1;
        printf("You picked up the Sword!\n");
    } else printf("Invalid action.\n");
}

void room_library(GameState *state, char *input) {
    if (strcmp(input, "w") == 0 || strcmp(input, "west") == 0) state->current_room = 1;
    else if (strcmp(input, "n") == 0 || strcmp(input, "north") == 0) state->current_room = 3;
    else if (strstr(input, "torch")) {
        state->has_torch = 1;
        printf("You grabbed the Torch!\n");
    } else printf("Invalid action.\n");
}

void room_treasure(GameState *state, char *input) {
    if (strcmp(input, "s") == 0 || strcmp(input, "south") == 0) state->current_room = 4;
    else if (strcmp(input, "w") == 0 || strcmp(input, "west") == 0) state->current_room = 2;
    else if (strstr(input, "chest") || strstr(input, "open")) {
        if (state->has_key) {
            printf("\n!!! YOU FOUND THE GOLD !!!\n");
            state->won = 1;
            state->game_over = 1;
        } else {
            printf("It's locked tight. You need a key.\n");
        }
    } else printf("Invalid action.\n");
}

void room_corridor(GameState *state, char *input) {
    if (strcmp(input, "w") == 0 || strcmp(input, "west") == 0) state->current_room = 3;
    else if (strcmp(input, "s") == 0 || strcmp(input, "south") == 0) state->current_room = 0;
    else if (strcmp(input, "n") == 0 || strcmp(input, "north") == 0) {
        if (state->has_torch) state->current_room = 5;
        else printf("It's too dark! You need a light source (Torch).\n");
    } else printf("Invalid action.\n");
}

void room_monster(GameState *state, char *input) {
    if (strcmp(input, "s") == 0 || strcmp(input, "south") == 0) state->current_room = 4;
    else if (strstr(input, "fight") || strstr(input, "attack")) {
        if (state->has_sword) {
            printf("With a mighty swing of your sword, the monster falls!\n");
            printf("You find a silver KEY on its collar.\n");
            state->has_key = 1;
            state->monster_alive = 0;
            state->current_room = 4; // Move player back after victory
        } else {
            state->health -= 40;
            printf("The monster claws you! You lose 40 health.\n");
            if (state->health <= 0) state->game_over = 1;
        }
    } else printf("The monster growls. You should 'fight' or 'run' (south)!\n");
}

void process_command(GameState *game, char *command) {
    // Basic Lowercase conversion
    for (int i = 0; command[i]; i++) if (command[i] < 91 && command[i] > 64) command[i] += 32;

    if (strcmp(command, "help") == 0) {
        printf("Commands: north, south, east, west, look, status, take [item], fight, open, quit\n");
        return;
    }
    if (strcmp(command, "status") == 0) { print_status(game); return; }
    if (strcmp(command, "quit") == 0) { game->game_over = 1; return; }
    if (strcmp(command, "look") == 0) { describe_room(game->current_room); return; }

    switch (game->current_room) {
        case 0: room_entrance(game, command); break;
        case 1: room_armory(game, command); break;
        case 2: room_library(game, command); break;
        case 3: room_treasure(game, command); break;
        case 4: room_corridor(game, command); break;
        case 5: room_monster(game, command); break;
    }
}

int main() {
    GameState game;
    char input[MAX_INPUT];
    init_game(&game);

    printf("Welcome to DUNGEON ADVENTURE!\n");
    describe_room(game.current_room);

    while (!game.game_over) {
        printf("\n> ");
        if (fgets(input, MAX_INPUT, stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0;
        
        process_command(&game, input);

        if (!game.game_over) {
            describe_room(game.current_room);
        }
    }

    // FINAL ENDING LOGIC
    if (game.won) {
        printf("\nCongratulations! You escaped with the treasure!\n");
        printf("FINAL SCORE: %d health remaining.\n", game.health);
    } else if (game.health <= 0) {
        printf("\nEverything goes dark... You died in the dungeon.\n");
    } else {
        printf("\nYou gave up on your quest. Goodbye.\n");
    }

    return 0;
}