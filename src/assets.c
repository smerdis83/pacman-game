#include "assets.h"
#include "raylib.h"

// Define textures as extern variables
Texture2D pacmanTextureRight;
Texture2D pacmanTextureLeft;
Texture2D pacmanTextureUp;
Texture2D pacmanTextureDown;
Texture2D wallTexture;
Texture2D pathTexture;
Texture2D starTexture;
Texture2D ghostTexture;
Texture2D scaredghostTexture;
//Texture2D ghostlTexture;
//Texture2D ghostdTexture;
//Texture2D ghostuTexture;

Texture2D appleTexture;
Texture2D mushTexture;
Texture2D pepperTexture;
Texture2D cherryTexture;


Sound deathMusic;
Sound backMusic;
Sound gameMusic;
Sound damageMusic;
Sound eatingMusic;
Sound healMusic;
Sound speedMusic;
Sound alertMusic;

void LoadAssets() {
    // Load textures from files (ensure you have the correct path)
    pacmanTextureRight = LoadTexture("..\\assets\\images\\pright.png");
    pacmanTextureLeft = LoadTexture("..\\assets\\images\\pleft.png");
    pacmanTextureUp = LoadTexture("..\\assets\\images\\pup.png");
    pacmanTextureDown = LoadTexture("..\\assets\\images\\pdown.png");
    wallTexture = LoadTexture("..\\assets\\images\\wall.png");
    pathTexture = LoadTexture("..\\assets\\images\\path.png");
    starTexture = LoadTexture("..\\assets\\images\\star.png");
    ghostTexture = LoadTexture("..\\assets\\images\\ghost.png");
    scaredghostTexture = LoadTexture("..\\assets\\images\\scared.png");
//    ghostlTexture = LoadTexture("C:\\Users\\bardia\\CLionProjects\\untitled1\\assets\\images\\ghostl.png");
//    ghostuTexture = LoadTexture("C:\\Users\\bardia\\CLionProjects\\untitled1\\assets\\images\\ghostu.png");
//    ghostdTexture = LoadTexture("C:\\Users\\bardia\\CLionProjects\\untitled1\\assets\\images\\ghostd.png");
    appleTexture = LoadTexture("..\\assets\\images\\apple.png");
    mushTexture = LoadTexture("..\\assets\\images\\mush.png");
    pepperTexture = LoadTexture("..\\assets\\images\\pepper.png");
    cherryTexture = LoadTexture("..\\assets\\images\\cherry.png");
    deathMusic = LoadSound("..\\assets\\musics\\pacman_death.wav");
    backMusic = LoadSound("..\\assets\\musics\\backg.mp3");
    gameMusic = LoadSound("..\\assets\\musics\\jazz.mp3");
    damageMusic = LoadSound("..\\assets\\musics\\damage.mp3");
    eatingMusic = LoadSound("..\\assets\\musics\\eating.mp3");
    speedMusic = LoadSound("..\\assets\\musics\\speed.mp3");
    healMusic = LoadSound("..\\assets\\musics\\heal.mp3");
    alertMusic = LoadSound("..\\assets\\musics\\alert.mp3");
    //mainMusic = LoadMusicStream("C:\\Users\\bardia\\CLionProjects\\untitled1\\assets\\musics\\death.wav")
}

void UnloadAssets() {
    // Unload textures when no longer needed
    UnloadTexture(pacmanTextureUp);
    UnloadTexture(pacmanTextureDown);
    UnloadTexture(pacmanTextureLeft);
    UnloadTexture(pacmanTextureRight);
    UnloadTexture(wallTexture);
    UnloadTexture(pathTexture);
    UnloadTexture(starTexture);
    UnloadTexture(ghostTexture);
//    UnloadTexture(ghostdTexture);
//    UnloadTexture(ghostuTexture);
//    UnloadTexture(ghostlTexture);
    UnloadTexture(appleTexture);
    UnloadTexture(pepperTexture);
    UnloadTexture(mushTexture);
    UnloadSound(deathMusic);
    UnloadTexture(cherryTexture);
    UnloadTexture(scaredghostTexture);
    UnloadSound(backMusic);
    UnloadSound(gameMusic);
    UnloadSound(damageMusic);
    UnloadSound(eatingMusic);
    UnloadSound(healMusic);
    UnloadSound(speedMusic);
    UnloadSound(alertMusic);

}


