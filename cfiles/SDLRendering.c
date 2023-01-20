#include "SDLRendering.h"
//Variables for the renderer and window
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
static char filepath[] = "../imgs";

//Background related variables
SDL_Texture* backgroundTex; //the bg texture to be tiled
SDL_Texture* spriteSheet;
SDL_Texture* buildingSheet;
SDL_Texture* arrow;
//size of the map in pixels
int sizeX;
int sizeY;
//number of times the texture must be repeated
int repeatsX;
int repeatsY;
//width and height of the background texture
int bgWidth;
int bgHeight;

//location of the top left corner of the camera
int cameraX;
int cameraY;

//size of the window in pixels
int screenX;
int screenY;

//the size of the sprites on the spritesheet, in pixels
short spriteSize;

//prints a renderer error with decent formatting
void printError(char msg[]) {
    printf("%s\nError: %s",msg, SDL_GetError());
}

//initialises SDL, the window and the renderer
int init(int x, int y) { //return 0 if successful, 1 otherwise
    //Create the window
    window = SDL_CreateWindow("Hello World!", 0, 0, 0, 0, SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(window == NULL) {
        printError("Error making the window");
        return 1;
    }
    //Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        printError("Error making renderer");
        SDL_DestroyWindow(window);
        return 1;
    }
    sizeX = x;
    sizeY = y;
    SDL_GetWindowSize(window, &screenX, &screenY);
    TTF_Init();
    return 0;

}

//creates a texture from an image, returns the texture
SDL_Texture* loadTexture(char img[]) {
    SDL_Surface *surface = IMG_Load(img);
    if(surface == NULL) {
        printf("Error creating surface for %s\nError: %s\n"
        , img, SDL_GetError());
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(surface == NULL) {
        printf("Error creating texture for %s\nError: %s\n"
        , img, SDL_GetError());
        return NULL;
    }
    SDL_FreeSurface(surface);
    return texture;
}

void loadProjectiles() {
    arrow = loadTexture("../imgs/arrow.png");
}

void loadBuildings(char buildings[]) {
    buildingSheet = loadTexture(buildings);
}

void initTextures() {
    loadProjectiles();
    loadBuildings("../imgs/buildings.png");
}


//renders a given texture at its size, basically just used for the background
void renderTexture(SDL_Texture *texture, int x, int y) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}


//renders a sprite, given its position, size, position on the sprite sheet
//useful for rendering units
void renderSprite(SDL_Texture *texture, int x, int y, int spritex, int spritey,
    int spriteSize, short unitSize) {
    SDL_Rect src;
    SDL_Rect dst;
    src.x = spritex;
    src.y= spritey;
    src.w=spriteSize;
    src.h = spriteSize;
    dst.x = x;
    dst.y = y;
    dst.w = unitSize;
    dst.h = unitSize;
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

/*initialises and displays background, given a texture and size of the map
inputs are: size of map in x and y directions, size of texture
in x and y directions, texture*/
//returns 0 if succesful, 1 otherwise
int initBackground(char tex[]) {
    backgroundTex = loadTexture(tex);
    if(SDL_QueryTexture(backgroundTex, NULL, NULL, &bgWidth, &bgHeight) == 0) {
        repeatsX = sizeX / bgWidth;
        repeatsY = sizeY / bgHeight;
        return 0;

    }
    else {
        return 1;
    }
}

//initialises sprite sheet
int initSpritesheet(char sheet[], short setSpriteSize) {
    spriteSheet = loadTexture(sheet);
    if(spriteSheet == NULL) {
        printError("Error loading sprite sheet");
        return 1;
    }
    spriteSize = setSpriteSize;
    return 0;
}

//Calculate position on screen from position on the map
int screenPosX(int realx, int camX) {return(realx - camX);}
int screenPosY(int realy, int camY) {return (realy - camY);}

//does the reverse of the above functions
//at time of writing, used for finding where on the map the user clicked
int globalPos(int screen, int cam) {return(screen + cam);}

//Returns current location of the camera
void getCamLoc(int *x, int *y) {
    *x = cameraX;
    *y = cameraY;
}

//Adds background to renderer
void renderBackground() {
    int curCamX = cameraX;
    int curCamY = cameraY;
    int x, y;
    for(x = 0; x < repeatsX; x++) {
        for(y = 0; y < repeatsY; y++) {
            renderTexture(
                backgroundTex, screenPosX(x*bgWidth, curCamX), screenPosY(y*bgHeight, curCamY)
            );
        }
    }
}

//functions to move the camera on the x and y axes
//Allows the camera to be 25 pixels over the edge of the map
void moveCamx(int dist) {
    if(!(cameraX < 0 && dist < 0) &&
     !(cameraX > (sizeX - screenX) && dist > 0)) {
        cameraX += dist;
    }
}
void moveCamy(int dist) {
    if(!(cameraY < 0 && dist < 0) && !(cameraY > (sizeY - screenY) && dist > 0)) {
        cameraY += dist;
    }
}

//renders all the units in the linked list, as well as projectiles
void renderUnits() {
    unit *currentUnit = firstUnit;
    if(currentUnit->unitAfter == NULL) {
        return; //no units exist
    }

    SDL_Rect healthbar;
    healthbar.h=5;
    int curCamX = cameraX;
    int curCamY = cameraY;
    int renderx;
    int rendery;
    int spritex;
    int spritey;
    short unitSize;
    SDL_SetRenderDrawColor(renderer, 144,255,144,255);
    while(currentUnit->unitAfter != NULL) {
        currentUnit = currentUnit->unitAfter;
         renderx = screenPosX(currentUnit->x, curCamX);
         rendery = screenPosY(currentUnit->y, curCamY);
         unitSize = currentUnit->size;
         if(currentUnit->team == 0) {spritey = 0;}
         else {spritey = 100;}
         switch(currentUnit->typeID) {
             case 0: //warrior
                spritex=0;
                break;
            case 1: //scout
                spritex=100;
                break;
            case 2: //archer
                spritex=200;
                break;
            default:
                spritex = 0; //if it hasn't been given a texture, just use a warrior
                break;
         }
         renderSprite(spriteSheet, renderx, rendery, spritex, spritey,
         spriteSize, unitSize);
         //for the health bar
         float percentagehealth =
         (float)currentUnit->health / (float)currentUnit->maxhealth;
         short healthbarSize = unitSize * percentagehealth;
         healthbar.w = healthbarSize;
         healthbar.x = renderx;
         healthbar.y = rendery - 5;
         SDL_RenderDrawRect(renderer, &healthbar);
         SDL_RenderFillRect(renderer, &healthbar);

    }
    //render projectiles
     projectile *curProj = firstProjectile;
     int projrenderx;
     int projrendery;
     while(curProj->projectileAfter != NULL) {
        curProj = curProj->projectileAfter;
        projrenderx = screenPosX(curProj->x, curCamX);
        projrendery = screenPosY(curProj->y, curCamY);
        int projWidth = 16;
        int projHeight = 4;
        //projrender is the deadly zone of the projectile, which needs
        //to be at the front-middle of the projectile. Some transformations
        //are thus applied to the texture and render location to make this so

        SDL_Rect projRect;
        projRect.x = projrenderx - projWidth;
        projRect.y = projrendery;
        projRect.w = projWidth;
        projRect.h = projHeight;
        SDL_Point point;
        point.x = projWidth;
        point.y = projHeight/2;
        SDL_RenderCopyEx(renderer, arrow, NULL, &projRect,
        curProj->angle, &point, SDL_FLIP_NONE);
    }

    //draw a rectangle around the currently actively selected unit
    if(activeUnit != NULL) {
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        int camerax, cameray;
        getCamLoc(&camerax, &cameray);
        SDL_Rect activeRect;
        activeRect.x = screenPosX(activeUnit->x, camerax);
        activeRect.y = screenPosY(activeUnit->y, cameray);
        activeRect.w = activeUnit->size;
        activeRect.h = activeUnit->size;
        SDL_RenderDrawRect(renderer, &activeRect);
    }
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}

//renders buildings
void renderBuildings() {
    building *curBuild = firstBuilding;
    int renderx, rendery, spritex, spritey;
    int curCamX = cameraX;
    int curCamY = cameraY;
    while(curBuild->buildingAfter != NULL) {
        curBuild = curBuild->buildingAfter;
        renderx = screenPosX(curBuild->x, curCamX);
        rendery = screenPosY(curBuild->y, curCamY);
        if(curBuild->typeID == 0) {
            spritex=0;
        }
        else {spritex = 0;}
        if(curBuild->team == 0) {
            spritey = 0;
        }
        else if(curBuild->team == 1) {
            spritey = 100;
        }
        else {spritey = 0;}
        renderSprite(buildingSheet, renderx, rendery, spritex, spritey,
        100, curBuild->size);

        //healthbar
        SDL_SetRenderDrawColor(renderer, 144,255,144,255);
        SDL_Rect healthbar;
        float percentagehealth =
        (float)curBuild->health / (float)curBuild->maxhealth;
        short healthbarSize = curBuild->size * percentagehealth;
        healthbar.w = healthbarSize;
        healthbar.h = 8;
        healthbar.x = renderx;
        healthbar.y = rendery - 8;
        SDL_RenderDrawRect(renderer, &healthbar);
        SDL_RenderFillRect(renderer, &healthbar);

        //building progress bar
        if(curBuild->buildTimeRemaining > 0) {
            SDL_SetRenderDrawColor(renderer, 204,133,34,255);
            SDL_Rect buildBar;
            float percentagedone = (float)curBuild->buildTimeRemaining
            /(float)curBuild->totalBuildTime;
            short buildBarSize = curBuild->size * percentagedone;
            buildBar.w = buildBarSize;
            buildBar.h = 8;
            buildBar.x = renderx;
            buildBar.y = rendery + curBuild->size;
            SDL_RenderDrawRect(renderer, &buildBar);
            SDL_RenderFillRect(renderer, &buildBar);
        }
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);

    }
    //set a box around the active building
    if(activeBuilding != NULL) {
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        int camerax, cameray;
        getCamLoc(&camerax, &cameray);
        SDL_Rect activeRect;
        activeRect.x = screenPosX(activeBuilding->x, camerax);
        activeRect.y = screenPosY(activeBuilding->y, cameray);
        activeRect.w = activeBuilding->size;
        activeRect.h = activeBuilding->size;
        SDL_RenderDrawRect(renderer, &activeRect);
    }
}

//renders the resources to the top left of the screen
void renderResources() {
    SDL_Color color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    TTF_Font *font = TTF_OpenFont("GeosansLight.ttf", 14);
    char playerOneStr[20];
    char playerTwoStr[20];
    int resOne = getResources(0);
    int resTwo = getResources(1);
    sprintf(playerOneStr, "P1: %d", resOne);
    sprintf(playerTwoStr, "P2: %d", resTwo);
    SDL_Surface *playerone = TTF_RenderText_Solid(font, playerOneStr, color);
    SDL_Surface *playertwo = TTF_RenderText_Solid(font, playerTwoStr, color);
    SDL_Texture *tex1 = SDL_CreateTextureFromSurface(renderer, playerone);
    SDL_Texture *tex2 = SDL_CreateTextureFromSurface(renderer, playertwo);
    renderTexture(tex1, 20, 100);
    renderTexture(tex2, 20, 150);
    TTF_CloseFont(font);
}

//Renders and displays everything
void renderAll() {
    renderBackground();
    renderBuildings();
    renderUnits();
    renderResources();
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

//destroys everything to prevent memory leaks
void shutDown() {
    SDL_DestroyTexture(backgroundTex);
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyTexture(arrow);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(buildingSheet);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
