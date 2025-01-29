#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"

// Declare texture variables (add more as needed)
extern Texture2D pacmanTextureUp;
extern Texture2D pacmanTextureDown;
extern Texture2D pacmanTextureRight;
extern Texture2D pacmanTextureLeft;
extern Texture2D wallTexture;
extern Texture2D pathTexture;
extern Texture2D starTexture;
extern Texture2D ghostTexture;
extern Texture2D scaredghostTexture;

extern Texture2D mushTexture;
extern Texture2D appleTexture;
extern Texture2D pepperTexture;
extern Texture2D cherryTexture;


extern Sound deathMusic;
extern Sound backMusic;
extern Sound gameMusic;
extern Sound damageMusic;
extern Sound eatingMusic;
extern Sound healMusic;
extern Sound speedMusic;
extern Sound alertMusic;

// Function declarations for asset loading and unloading
void LoadAssets();
void UnloadAssets();

#endif // ASSETS_H
