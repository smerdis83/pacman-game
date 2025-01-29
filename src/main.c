#include "raylib.h"
#include "game.h"
#include "record.h"
#include "menu.h"
#include "assets.h"
#include "difficulty.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
    InitWindow(1800, 1200, "Pacman Game");
    SetTargetFPS(60);
    InitAudioDevice();
    // Loads assets
    LoadAssets();

    int debounceCounter = 0;
    PlaySound(backMusic);
    bool background = true;

    while (!WindowShouldClose() && !exitGame) {
        if (state != MENU && state != RECORD && state != DIFF){
            if(IsSoundPlaying(backMusic)){
                StopSound(backMusic);
            }
        }
        else if (!IsSoundPlaying(backMusic)){
            PlaySound(backMusic);
        }
        if (state != GAMEPLAY){
            if (IsSoundPlaying(gameMusic)){
                StopSound(gameMusic);
            }
        }
        if (pacman.health == 0) {
            state = LOSE;
            PlaySound(deathMusic);
            //PlayMusicStream(deathMusic);
        }
        if (state == MENU) {

            if (debounceCounter == 0) { // Only process input if debounce is complete
                HandleMenuInput(); // Process menu input
            }

            RenderMenu();      // Draw the menu screen
        } else if (state == GAMEPLAY) {
            // Handle Pacman input and movement
            if (!IsSoundPlaying(gameMusic) && !IsSoundPlaying(alertMusic))
                PlaySound(gameMusic);

            setconsts();
            pacmanMoveCounter++;
            ghostMoveCounter++;
            // Rendering
            BeginDrawing();
            ClearBackground(BLACK);
            // Render game map and Pacman
            SpawnGhosts();
            SpawnFruit();
            HandlePacmanInput();
            MovePacman();
            HandleCollision();
            MoveGhosts();

            RenderMap();
            RenderCharacters();
            EndDrawing();
        } else if (state == LOSE) {

             // Ensure the record is saved only once
            pacman.health = 5;
                EndGameAndSaveRecord(score); // Ask for the player's name and save the record


            // After saving, transition to the menu
            if (IsKeyPressed(KEY_ENTER)) {
                 // Reset the flag for future use
                state = MENU;        // Go back to the main menu
            }

            // Display "You Lost" screen or any other message
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("You Lost!", 200, 50, 40, RED);
            DrawText("Press ENTER to go to the Menu", 100, 150, 20, WHITE);
            EndDrawing();
        }
        else if (state == RECORD){
            RenderRecordsScreen();
            if (IsKeyPressed(KEY_ENTER)) {
                // Reset the flag for future use
                state = MENU;// Go back to the main menu
                debounceCounter = 10;
            }
        }
        else if (state == DIFF){
            RenderdiffMenu();
            HandlediffMenuInput();
            if (IsKeyPressed(KEY_ENTER)) {
                // Reset the flag for future use
                state = MENU;// Go back to the main menu
                debounceCounter = 10;
            }
        }
        if (debounceCounter > 0){
            debounceCounter--;
        }

    }
    UnloadAssets();
    CloseWindow();
    return 0;
}
