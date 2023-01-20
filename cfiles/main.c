#include "main.h"

int stop = 0; //true when game must be stopped

//a function to be run in a seperate thread, that just renders
SDL_Event event;

void *timeFunc(void *input) {
  SDL_Delay(10);
}

//function to run all game logic, run in the main thread
void *controlFunc(void *input) {
  pthread_t timerThread;
  while(stop == 0) {
    pthread_create(&timerThread, NULL, timeFunc, NULL);
    short gameState = runEvents();
    if(gameState == 1) {
        stop = 1;
    }
    if(keyboardState() == 1) {
        stop = 1;
    }
    unitsLogic();
    cycleProjectiles();
    buildLogic();
    pthread_join(timerThread, NULL);
  }
}

//initialises, runs controls, rendering, and game logic in separate threads
void main() {

    pthread_t controlThread;

    init(5000,5000);
    initBackground("../imgs/maptexture.png");
    if(initSpritesheet("../imgs/spritesheet.png", 100) == 1) {
        printf("Error with spritesheet!\n");
        return;
    };

    //initialising various featuers
    initTextures();
    initUnits();
    initBuildings();

    //Setting up the pieces
    addBuilding(0, 100, 100, 0);
    addBuilding(0, 200, 100, 0);
    addBuilding(0, 300, 100, 0);
    addBuilding(0, 400, 100, 0);
    addBuilding(0, 500, 100, 0);
    addBuilding(0, 100, 700, 1);
    addBuilding(0, 200, 700, 1);
    addBuilding(0, 300, 700, 1);
    addBuilding(0, 400, 700, 1);
    addBuilding(0, 500, 700, 1);
    addResources(1, 10000);
    addResources(0, 10000);

        if(pthread_create(&controlThread, NULL, controlFunc, NULL)) {
            printf("Failed to create control thread!");
            return;
        }

        while(stop == 0) {
          renderAll();
        }
        if(pthread_join(controlThread, NULL)) {
            printf("Error rejoining control thread");
            exit(1);
        }
    removeAllUnits();
    removeAllBuildings();
    removeAllProjectiles();
    shutDown();
}
