#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "raylib.h"
#include "assets.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Initialize global variables
GameState state = MENU;
int game_difficulty = 2; // 1 easy 2 medium 3 hard
bool exitGame = false;

// Initialize the game map (walls and open spaces)
int gameMap[30][40] =  { // 5 apple 6 mush 7 pepper
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

        //{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        //{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
       // {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

};
int ghostmap[30][40];
int fruitmap[30][40];

// Initialize Pacman
Pacman pacman = {1, 1, 3,5}; // Starting position and direction (right)
// Movement delay variables
const int COLLISION_COOLDOWN = 30;
int pacmanMoveDelay = 10;   // Number of frames to wait before moving
int pacmanMoveCounter = 0;   // Counter to track frames
int ghostMoveCounter = 0;
int ghostMoveDelay = 15;
int coolDown = 0;
int fruit_coolDown = 0;
int pepper_coolDown = 900;
int cherry_coolDown = 900;

int score;                     // Current score
Vector2 stars[10];             // Array to store star positions
int starCount = 0;             // Current number of stars on the map
int ghostCount = 0;
int ghostCountInit = 5;
int StarCountInit = 10;

int appleFlag = 0;
int pepperFlag = 0;
int mushFlag = 0;
int cherryFlag = 0;

int cherry_allowed = 1;
int pepper_allowed = 1;
int ghost_eat = 0;

void setconsts(){
    if (game_difficulty == 1){
        StarCountInit = 20;
        ghostCountInit = 3;
        ghostMoveDelay = 20;
    }
    else if (game_difficulty == 2){
        StarCountInit = 10;
        ghostCountInit = 5;
        ghostMoveDelay = 15;
    }
    else{
        StarCountInit = 5;
        ghostCountInit = 10;
        ghostMoveDelay = 10;
    }
}
void RenderMap() {
    int tileSize = 32; // Adjust tile size based on your textures

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Vector2 position = { x * tileSize, y * tileSize };

            // Draw walls
            if (gameMap[y][x] == 1) {
                DrawTexture(wallTexture, position.x, position.y, WHITE);
            }
                // Draw paths
            else if (gameMap[y][x] == 0 && !(ghost_eat)) {
                DrawTexture(pathTexture, position.x, position.y, WHITE);
            }
                // Draw stars
            else if (gameMap[y][x] == 2) {
                if (!ghost_eat)
                    DrawTexture(pathTexture, position.x, position.y, WHITE); // Draw path under the star
                DrawTexture(starTexture, position.x + tileSize / 4, position.y + tileSize / 4, WHITE); // Center the star
            }
            if (fruitmap[y][x] == 4){
                DrawTexture(cherryTexture, position.x + tileSize / 4, position.y + tileSize / 4, WHITE);
            }
            else if (fruitmap[y][x] == 5) {
          //     DrawTexture(pathTexture, position.x, position.y, WHITE); // Draw path under the star
                DrawTexture(appleTexture, position.x + tileSize / 4, position.y + tileSize / 4, WHITE); // Center the star
            }
            else if (fruitmap[y][x] == 6) {
               // DrawTexture(pathTexture, position.x, position.y, WHITE); // Draw path under the star
                DrawTexture(mushTexture, position.x + tileSize / 4, position.y + tileSize / 4, WHITE); // Center the star
            }
            else if (fruitmap[y][x] == 7) {
             //   DrawTexture(pathTexture, position.x, position.y, WHITE); // Draw path under the star
                DrawTexture(pepperTexture, position.x + tileSize / 4, position.y + tileSize / 4, WHITE); // Center the star
            }
        }
    }
    char scoreText[20];
    char healthText[20];
    sprintf(scoreText, "Score: %d", score); // Format the score into the string
    DrawText(scoreText, 10, GetScreenHeight() - 100, 40, YELLOW); // Draw the score
    if (!(pepperFlag)){
        DrawText("GOING FAST!!",300,GetScreenHeight() - 100, 40,GREEN);
    }
    if (ghost_eat){
        DrawText("EAT THOSE GHOSTS!!", 700,GetScreenHeight() - 100,40,BLUE);
    }
    sprintf(healthText,"Health: %d",pacman.health);
    DrawText(healthText,GetScreenWidth() - 400,GetScreenHeight() - 100, 50, RED); // Draw the health
}
void RenderCharacters() {
    int tileSize = 32; // Same as map tiles

    Vector2 pacmanPos = { pacman.x * tileSize, pacman.y * tileSize };


    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (ghostmap[y][x] == 1){
                if (ghost_eat){
                    DrawTexture(scaredghostTexture,tileSize * x,tileSize * y, WHITE);
                }
                else {
                    DrawTexture(ghostTexture, tileSize * x, tileSize * y, WHITE);
                }
            }

        }
    }
    if (pacman.direction == 0) {  // Up
        DrawTexture(pacmanTextureUp, pacmanPos.x, pacmanPos.y, WHITE);
    } else if (pacman.direction == 1) {  // Down
        DrawTexture(pacmanTextureDown, pacmanPos.x, pacmanPos.y, WHITE);
    } else if (pacman.direction == 2) {  // Left
        DrawTexture(pacmanTextureLeft, pacmanPos.x, pacmanPos.y, WHITE);
    } else if (pacman.direction == 3) {  // Right
        DrawTexture(pacmanTextureRight, pacmanPos.x, pacmanPos.y, WHITE);
    }
}

void SpawnStars() {
    starCount = StarCountInit;
    srand(time(NULL));
    for (int i = 0; i < StarCountInit; i++) {
        int x, y;
        do {
            x = rand() % 40;
            y = rand() % 30;
        } while ((gameMap[y][x] == 1) || (x == pacman.x && y == pacman.y) || gameMap[y][x] == 2 || ghostmap[y][x] == 1 || fruitmap[y][x]); // Avoid walls and Pacman’s position and same star
        gameMap[y][x] = 2;
    }
}
void SpawnFruit(){
    srand(time(NULL));
    if (!cherryFlag && cherry_allowed){
        int x,y;
        do {
            x = rand() % 40;
            y = rand() % 30;
        } while ((gameMap[y][x] == 1) || (x == pacman.x && y == pacman.y) || gameMap[y][x] == 2 || ghostmap[y][x] == 1 || fruitmap[y][x] != 0 || gameMap[y][x]
                                                                                                                                                  == 2);
        fruitmap[y][x] = 4;
        cherryFlag = 1;
    }
    if (!mushFlag){
        int x, y;
        do {
            x = rand() % 40;
            y = rand() % 30;
        } while ((gameMap[y][x] == 1) || (x == pacman.x && y == pacman.y) || gameMap[y][x] == 2 || ghostmap[y][x] == 1 || fruitmap[y][x] != 0 || gameMap[y][x]
                                                                                                                                                 == 2); // Avoid walls and Pacman’s position and same star
        fruitmap[y][x] = 6;
        mushFlag = 1;
    }
    if (!appleFlag){
        int x, y;
        do {
            x = rand() % 40;
            y = rand() % 30;
        } while ((gameMap[y][x] == 1) || (x == pacman.x && y == pacman.y) || gameMap[y][x] == 2 || ghostmap[y][x] == 1 || fruitmap[y][x] != 0 || gameMap[y][x]
        == 2); // Avoid walls and Pacman’s position and same star
        fruitmap[y][x] = 5;
        appleFlag = 1;
    }
    if (!pepperFlag && pepper_allowed){
        int x, y;
        do {
            x = rand() % 40;
            y = rand() % 30;
        } while ((gameMap[y][x] == 1) || (x == pacman.x && y == pacman.y) || gameMap[y][x] == 2 || ghostmap[y][x] == 1 || fruitmap[y][x] != 0 || gameMap[y][x] == 2); // Avoid walls and Pacman’s position and same star
        fruitmap[y][x] = 7;
        pepperFlag = 1;
    }

}

void SpawnGhosts() {
    int to_add = ghostCountInit - ghostCount;
    ghostCount = ghostCountInit;
    srand(time(NULL));
    for (int i = 0; i < to_add; i++) {
        int x, y;
        do {
            x = rand() % 40;
            y = rand() % 30;
        } while ((gameMap[y][x] == 1) || (x == pacman.x && y == pacman.y) || ghostmap[y][x] == 1 || gameMap[y][x] == 2); // Avoid walls and Pacman’s position and same star
        ghostmap[y][x] = 1;
    }
}
//void MoveGhosts(){
//    if (ghostMoveCounter >= ghostMoveDelay) {
//        // Possible movement directions: {row offset, column offset}
//        int directions[4][2] = {{-1, 0},
//                                {1,  0},
//                                {0,  -1},
//                                {0,  1}};  // Up, Down, Left, Right
//
//        // Create a temporary copy of ghostsMap to avoid overwriting while iterating
//        int tempGhostsMap[MAP_HEIGHT][MAP_WIDTH] = {0};
//
//        for (int x = 0; x < MAP_WIDTH; x++) {
//            for (int y = 0; y < MAP_HEIGHT; y++) {
//                if (ghostmap[y][x] == 1) {  // If there's a ghost at (i, j)
//                    int newX = x, newY = y;
//                    int validMove = 0;
//
//                    // Try to find a valid random move
//                    for (int attempts = 0; attempts < 4; attempts++) {
//                        int direction = rand() % 4;  // Pick a random direction
//                        newX = x + directions[direction][0];
//                        newY = y + directions[direction][1];
//
//                        // Check if the new position is within bounds and valid
//                        if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
//                            gameMap[newY][newX] != 1 && tempGhostsMap[newY][newX] == 0) {
//                            validMove = 1;
//                            break;
//                        }
//                    }
//
//                    // If a valid move is found, move the ghost
//                    if (validMove) {
//                        tempGhostsMap[newY][newX] = 1;  // Move ghost to new position
//                    } else {
//                        tempGhostsMap[y][x] = 1;  // Keep the ghost in place if no move is valid
//                    }
//                }
//            }
//        }
//
//        // Update the original ghostsMap with the new positions
//        for (int i = 0; i < MAP_WIDTH; i++) {
//            for (int j = 0; j < MAP_HEIGHT; j++) {
//                ghostmap[j][i] = tempGhostsMap[j][i];
//            }
//        }
//        ghostMoveCounter = 0;
//    }
//}
void MoveGhosts() {
    if (ghostMoveCounter >= ghostMoveDelay) {
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right
        int tempGhostsMap[MAP_HEIGHT][MAP_WIDTH] = {0};

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (ghostmap[y][x] == 1) { // Ghost found

                    // Shuffle directions for randomness
                    for (int i = 0; i < 4; i++) {
                        int swap = rand() % 4;
                        int temp[2] = {directions[i][0], directions[i][1]};
                        directions[i][0] = directions[swap][0];
                        directions[i][1] = directions[swap][1];
                        directions[swap][0] = temp[0];
                        directions[swap][1] = temp[1];
                    }

                    int moved = 0;
                    for (int i = 0; i < 4; i++) {
                        int newX = x + directions[i][0];
                        int newY = y + directions[i][1];

                        // Check bounds and validity
                        if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
                            gameMap[newY][newX] != 1 && tempGhostsMap[newY][newX] == 0) {
                            tempGhostsMap[newY][newX] = 1; // Move ghost
                            moved = 1;
                            break;
                        }
                    }

                    if (!moved) {
                        tempGhostsMap[y][x] = 1; // Stay in place if no valid move
                    }
                }
            }
        }

        // Update the main ghost map
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                ghostmap[y][x] = tempGhostsMap[y][x];
            }
        }

        ghostMoveCounter = 0; // Reset move counter
    }
}
void HandleCollision() {
    // Get Pacman's tile position
    int pacmanTileX = pacman.x;  // Pacman's X coordinate in tile units
    int pacmanTileY = pacman.y;  // Pacman's Y coordinate in tile units

    // Check if the tile contains a star
    if (gameMap[pacmanTileY][pacmanTileX] == 2) {
        gameMap[pacmanTileY][pacmanTileX] = 0;  // Remove the star from the map
        starCount--;
        score += 10;  // Increase score for collecting the star
        PlaySound(eatingMusic);
        // Optional: Play sound or effect for collecting a star
        // PlaySound(starCollectSound);
    }

    // Handle collision with ghost
    if (ghostmap[pacmanTileY][pacmanTileX] == 1) {
        // Check if the cooldown has expired
        if (!(ghost_eat)) {
            if (coolDown == 0) {
                pacman.health--;  // Deduct health
                coolDown = COLLISION_COOLDOWN;  // Reset the cooldown
                PlaySound(damageMusic);
            }

            // Check if Pacman has died
            if (pacman.health == 0) {
                state = LOSE;  // Set game state to "lose"
            }
        }
        else{
            if(coolDown == 0){
                ghostmap[pacmanTileY][pacmanTileX] = 0;
                score += 50;
                coolDown = COLLISION_COOLDOWN;
                ghostCount--;
                PlaySound(eatingMusic);
            }
        }
    }

    // Decrease the cooldown timer if it's active
    if (coolDown > 0) {
        coolDown--;
    }

    // Check if all stars are collected
    if (starCount == 0) {
        // Respawn 10 new stars
        SpawnStars();
    }
    if (fruitmap[pacmanTileY][pacmanTileX] == 5){
        if (fruit_coolDown == 0) {
            pacman.health++;
            fruitmap[pacmanTileY][pacmanTileX] = 0;
            appleFlag = 0;
            fruit_coolDown = COLLISION_COOLDOWN;
            PlaySound(healMusic);
        }
    }
    if (fruitmap[pacmanTileY][pacmanTileX] == 6){
        if (fruit_coolDown == 0) {
            pacman.health--;
            fruitmap[pacmanTileY][pacmanTileX] = 0;
            mushFlag = 0;
            if (pacman.health == 0) {
                state = LOSE;
            }
            PlaySound(damageMusic);
        }
    }
    if (fruitmap[pacmanTileY][pacmanTileX] == 7){
        if (fruit_coolDown == 0) {
            pacmanMoveDelay = 5;
            fruitmap[pacmanTileY][pacmanTileX] = 0;
            pepperFlag = 0;
            pepper_allowed = 0;

        }
    }
    if (pepper_coolDown > 0 && !(pepperFlag)){
        if (!IsSoundPlaying(speedMusic))
            PlaySound(speedMusic);
        pepper_coolDown--;
    }
    if (pepper_coolDown == 0){
        pepper_coolDown = 900;
        pepper_allowed = 1;
        pacmanMoveDelay = 10;
        if(IsSoundPlaying(speedMusic))
            StopSound(speedMusic);
    }

    if (fruitmap[pacmanTileY][pacmanTileX] == 4){
        if (fruit_coolDown == 0) {
            ghost_eat = 1;
            fruitmap[pacmanTileY][pacmanTileX] = 0;
            cherryFlag = 0;
            cherry_allowed = 0;
            PlaySound(eatingMusic);
            if (IsSoundPlaying(gameMusic))
                StopSound(gameMusic);
        }
    }
    if (cherry_coolDown > 0 && !(cherryFlag)){
        if (!IsSoundPlaying(alertMusic))
            PlaySound(alertMusic);
        cherry_coolDown--;
    }
    if (cherry_coolDown == 0){
        cherry_coolDown = 900;
        cherry_allowed = 1;
        ghost_eat = 0;
        if (IsSoundPlaying(alertMusic))
            StopSound(alertMusic);
        if (!IsSoundPlaying(gameMusic))
            PlaySound(gameMusic);
    }
    if (fruit_coolDown > 0){
        fruit_coolDown--;
    }
    SpawnFruit();
}


// Move Pacman based on the current direction
void MovePacman() {
    if (pacmanMoveCounter >= pacmanMoveDelay) {
        int newX = pacman.x;
        int newY = pacman.y;

        // Handle movement based on direction
        if (pacman.direction == 0) {  // Up
            newY -= 1;
        } else if (pacman.direction == 1) {  // Down
            newY += 1;
        } else if (pacman.direction == 2) {  // Left
            newX -= 1;
        } else if (pacman.direction == 3) {  // Right
            newX += 1;
        }

        // Check if the new position is within bounds and not a wall
        if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT) {
            if (gameMap[newY][newX] == 0 || gameMap[newY][newX] == 2) {
                pacman.x = newX;
                pacman.y = newY;
            }
        }

        // Reset the move counter
        pacmanMoveCounter = 0;
    }
}

void HandlePacmanInput() {
    if (pacmanMoveCounter >= pacmanMoveDelay) {
        int nextX = pacman.x; // Current X position of Pacman
        int nextY = pacman.y; // Current Y position of Pacman

        // Check UP
        if (IsKeyDown(KEY_UP)) {
            nextY = pacman.y - 1; // Tile above
            if (gameMap[nextY][nextX] == 0 || gameMap[nextY][nextX] == 2) {
                pacman.direction = 0; // Up
            }
        }

        // Check DOWN
        if (IsKeyDown(KEY_DOWN)) {
            nextY = pacman.y + 1; // Tile below
            if (gameMap[nextY][nextX] == 0 || gameMap[nextY][nextX] == 2) {
                pacman.direction = 1; // Down
            }
        }

        // Check LEFT
        if (IsKeyDown(KEY_LEFT)) {
            nextX = pacman.x - 1; // Tile to the left
            if (gameMap[pacman.y][nextX] == 0 || gameMap[pacman.y][nextX] == 2) {
                pacman.direction = 2; // Left
            }
        }

        // Check RIGHT
        if (IsKeyDown(KEY_RIGHT)) {
            nextX = pacman.x + 1; // Tile to the right
            if (gameMap[pacman.y][nextX] == 0 || gameMap[pacman.y][nextX] == 2) {
                pacman.direction = 3; // Right
            }
        }
    }
}
