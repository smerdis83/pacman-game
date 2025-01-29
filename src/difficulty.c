//
// Created by bardia on 1/12/2025.
//
#include "raylib.h"
#include "difficulty.h"
#include "game.h"


#define EASY 0
#define MEDIUM 1
#define HARD 2


// Static variable for menu selection
static int menuOption = 0;

void HandlediffMenuInput() {
    if (IsKeyPressed(KEY_DOWN)) {
        menuOption++;
        if (menuOption > HARD) menuOption = EASY; // Loop back to the top
    }
    if (IsKeyPressed(KEY_UP)) {
        menuOption--;
        if (menuOption < EASY) menuOption = HARD; // Loop back to the bottom
    }

    if (IsKeyPressed(KEY_ENTER)) {
        game_difficulty = menuOption + 1;
    }
}

void RenderdiffMenu() {
    BeginDrawing();
    ClearBackground(BLACK);

    // Title
    DrawText("PACMAN GAME", 200, 100, 40, YELLOW);

    // Menu options
    Color EColor = (menuOption == EASY) ? RED : WHITE;
    Color MColor = (menuOption == MEDIUM) ? RED : WHITE;
    Color HColor = (menuOption == HARD) ? RED : WHITE;


    DrawText("EASY", 250, 200, 30, EColor);
    DrawText("MEDIUM", 250, 250, 30, MColor);
    DrawText("HARD",250,300,30,HColor);


    EndDrawing();
}
