/*SDLRendering.c contains all content responsible for rendering the current
state of the game to the map, starting the renderer, and responsibly closing
all SDL objects upon closing the game*/

#ifndef _SDLLIBS_
#define _SDLLIBS_
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#endif

#ifndef _IOLIBS_
#define _IOLIBS_
#include<stdio.h>
#endif

#ifndef _UNITSTRUCTS_
#define _UNITSTRUCTS_
#include "unitStructs.h"
#endif

#ifndef _RESOURCES_
#define _RESOURCES_
#include "resources.h"
#endif

//initialises the game map at the specified x and y values
int init(int x, int y);

//loads the given texture, returns a pointer to it. Only used internally except
//in tests
SDL_Texture* loadTexture(char img[]);

//initialises the background, given a texture to use fo the background
int initBackground(char tex[]);

//initialises the sprite sheet for units, given both the name of the spriteSheet
//and the size in pixels of the sprites within it (sprites must be square)
int initSpritesheet(char sheet[], short setSpriteSize);

//must be run every render loop, renders everything
void renderAll();

//shuts down SDL
void shutDown();

//moves the camera dist pixels along the x or y axis
void moveCamx(int dist);
void moveCamy(int dist);

//returns the x and y location of the camera to the pointers provided
void getCamLoc(int *x, int *y);

//returns the position on the map of a position on the camera, given both
//current screen location and click location
int globalPos(int screen, int cam);

//initialises textures for projectiles and buildings
void initTextures();
