//a function that quickly provides a few units to play with
//so that one can test various unit interactions
#include "main.h"

short stopRendering = 1;
short stopGame = 0;

//a function to be run in a seperate thread, that just renders
void *renderFunc(void *input) {
    while(stopRendering != 0) {
        renderAll();
    }
    return NULL;
}
SDL_Event event;
//function to run all game logic, run in the main thread

void *controlFunc(void *input) {
    short gameState = runEvents();
    if(gameState == 1) {
        stopGame = 1;
        stopRendering=0;
    }
    if(keyboardState() == 1) {
        stopGame = 1;
        stopRendering=0;
    }
    unitsLogic();
    cycleProjectiles();
}

//initialises, runs controls, rendering, and game logic in separate threads
void main() {

    pthread_t controlThread;
    pthread_t renderThread;

    init(2000,2000);
    initBackground("../imgs/maptexture.png");
    if(initSpritesheet("../imgs/spritesheet.png", 100) == 1) {
        printf("Error with spritesheet!\n");
        return;
    };
    initUnits();
    int i;
    for(i = 100; i < 600; i = i + 100) {
        addUnit(0, i, 100, 0); //adds five warriors for team 0
        addUnit(2, i, 600, 1); //adds five archers for team 1
    }
    for(i = 700; i < 1100; i = i + 100) {
        addUnit(2, i, 100, 0); //5 archers for team 0
        addUnit(0, i, 600, 1); //5 warriors for team 1
        addUnit(1, i, i, 0); //just throws about some scounts for team 0
    }
    addUnit(1, -100, -100, 0);
    addUnit(1, 2000, 2000, 1);
    addUnit(3, 1000, 1000, 1); //big ol' test boy
    if(
        pthread_create(&renderThread, NULL, renderFunc, NULL)
    )
    {
        printf("Failed to create render thread!");
        return;
    }

    while(stopGame == 0) {
        if(
            pthread_create(&controlThread, NULL, controlFunc, NULL)
        )
        {
            printf("Failed to create control thread!");
            return;
        }
        SDL_Delay(10); //how long the delay is between game loops
        if(pthread_join(controlThread, NULL)) {
            printf("Error rejoining control thread");
            shutDown();
            return;
        }
    }
    pthread_join(renderThread, NULL);
    removeAllUnits();
    shutDown();
}
