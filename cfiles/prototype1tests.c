//a short snippet of code to test map scrolling functionality automatically
//and thoroughly

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
    }
    if(keyboardState() == 1) {
        stopGame = 1;
    }

}

//initialises, runs controls, rendering, and game logic in separate threads

void main() {
    //setup
    pthread_t controlThread;
    pthread_t renderThread;



    //testing "init" function
    printf("Creating at 300*300\n");
    init(300,300);
    initBackground("../imgs/maptexture.png");
    initUnits();
    renderAll();
    SDL_Delay(2000);
    shutDown();
    printf("Creating at 1366*768, monitor size\n");
    init(1366, 768);
    initBackground("../imgs/maptexture.png");
    renderAll();
    SDL_Delay(2000);
    shutDown();
    printf("Creating at 5000 * 5000\n");
    init(5000,5000);
    initBackground("../imgs/maptexture.png");
    renderAll();
    SDL_Delay(2000);
    shutDown();


    //testing "initBackground"
    init(5000,5000);
    initBackground("../imgs/tiles.jpeg");
    renderAll();
    SDL_Delay(2000);
    shutDown();

    init(5000,5000);
    initBackground("../imgs/testtex3.jpg");
    renderAll();
    SDL_Delay(2000);
    shutDown();

    //test a texture that does not exist
    init(5000,5000);
    if(initBackground("asdfasfadfsdfasd")) {
        printf("Texture does not exist!\n");
        shutDown();
    }
    else {
        printf("Texture should not exist, yet it does!\n");
        shutDown();
    }
    SDL_Delay(2000);

    //testing move camera, x and y
    init(5000, 5000);
    initBackground("../imgs/maptexture.png");
    for(int i = 0; i < 5000; i++) { //moves to bottom right
        moveCamx(1);
        moveCamy(1);
        renderAll();
    }
    for(int i = 0; i < 5000; i++) {//move to bottom left
        moveCamx(-1);
        moveCamy(1);
        renderAll();
    }
    for(int i = 0; i < 5000; i++) { //move to top right
        moveCamx(1);
        moveCamy(-1);
        renderAll();
    }
    for(int i = 0; i < 5000; i++) {//move to top left
        moveCamx(-1);
        moveCamy(-1);
        renderAll();
    }

    //testing camera controls with keyboard
    if(
        pthread_create(&renderThread, NULL, renderFunc, NULL)
    )
    {
        printf("Failed to create render thread!\n");
        return;
    }

    while(stopGame == 0) {
        if(
            pthread_create(&controlThread, NULL, controlFunc, NULL)
        )
        {
            printf("Failed to create control thread!\n");
            return;
        }
        SDL_Delay(10); //how long the delay is between game loops
        if(pthread_join(controlThread, NULL)) {
            printf("Error rejoining control thread\n");
            shutDown();
            return;
        }
    }
    shutDown();
}
