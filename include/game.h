#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

// Game state
typedef enum GameState {
    MENU,
    GAMEPLAY,
    LOSE,
    RECORD,
    DIFF
} GameState;

// Game variables
extern GameState state;
extern int game_difficulty;
extern bool exitGame;
extern int pacmanMoveDelay;
extern int pacmanMoveCounter;
extern int ghostMoveCounter;
extern int ghostMoveDelay;
extern int ghostCountInit;
extern int StarCountInit;


#define MAP_WIDTH  40   // Increased map width
#define MAP_HEIGHT 30   // Increased map height

// Game map array
extern int gameMap[MAP_HEIGHT][MAP_WIDTH];
extern int ghostmap[MAP_HEIGHT][MAP_WIDTH];
extern int fruitmap[MAP_HEIGHT][MAP_WIDTH];

// Pacman struct
typedef struct {
    int x, y; // Pacman's position on the map
    int direction;// Pacman's current movement direction
    int health;
} Pacman;

extern Pacman pacman;
extern int score;
void MovePacman();
void HandlePacmanInput();
void RenderMap();
void RenderCharacters();
void SpawnStars();     // Spawn 10 stars randomly
void HandleCollision(); // Handle collision with stars
void SpawnGhosts();
void MoveGhosts();
void SpawnFruit();
void setconsts();

#endif // GAME_H
