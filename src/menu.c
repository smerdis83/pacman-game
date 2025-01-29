#include "menu.h"
#include "raylib.h"
#include "game.h" // Assuming `state` and `exitGame` are defined in game.h

// Menu options as constants
#define PLAY_OPTION 0
#define RECORD_OPTION 1
#define DIFF_OPTION 2
#define EXIT_OPTION 3

// Static variable for menu selection
static int menuOption = 0;

void HandleMenuInput() {
    if (IsKeyPressed(KEY_DOWN)) {
        menuOption++;
        if (menuOption > EXIT_OPTION) menuOption = PLAY_OPTION; // Loop back to the top
    }
    if (IsKeyPressed(KEY_UP)) {
        menuOption--;
        if (menuOption < PLAY_OPTION) menuOption = EXIT_OPTION; // Loop back to the bottom
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (menuOption == PLAY_OPTION) {
            state = GAMEPLAY; // Switch to gameplay state
        } else if (menuOption == RECORD_OPTION) {
            state = RECORD;
        }else if (menuOption == DIFF_OPTION){
            state = DIFF;
        }
        else if (menuOption == EXIT_OPTION) {
            exitGame = true; // Exit the game
        }
    }
}

void RenderMenu() {
    BeginDrawing();
    ClearBackground(BLACK);

    // Title
    DrawText("PACMAN GAME", 200, 100, 40, YELLOW);

    // Menu options
    Color playColor = (menuOption == PLAY_OPTION) ? RED : WHITE;
    Color recordColor = (menuOption == RECORD_OPTION) ? RED : WHITE;
    Color diffColor = (menuOption == DIFF_OPTION) ? RED : WHITE;
    Color exitColor = (menuOption == EXIT_OPTION) ? RED : WHITE;

    DrawText("Play", 250, 200, 30, playColor);
    DrawText("Record", 250, 250, 30, recordColor);
    DrawText("Select difficutly",250,300,30,diffColor);
    DrawText("Exit", 250, 350, 30, exitColor);

    EndDrawing();
}
