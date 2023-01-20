#include "controls.h"
//contains reading and using of controls, moving of camera, other user input

//speed at which the camera moves
const int camSpeed = 5;


//from a map location, checks if a unit is at that location
//returns the pointer if there is one, returns NULL otherwise
unit* checkClickUnit(int x, int y) {
    unit *curUnit = firstUnit;
    while(curUnit->unitAfter != NULL) {
        curUnit = curUnit->unitAfter;
        int size = curUnit->size;
        int xval = x - curUnit->x;
        int yval = y - curUnit->y;
        if(xval > 0 && yval > 0 && xval < size && yval < size) {
            return curUnit;
        }
    }
    return NULL;
}

//returns pointer of a building that exists under a map location, if one exists
building* checkClickBuilding(int x, int y) {
    building *curBuild = firstBuilding;
    while(curBuild->buildingAfter != NULL) {
        curBuild = curBuild->buildingAfter;
        int size = curBuild->size;
        int xval = x - curBuild->x;
        int yval = y - curBuild->y;
        if(xval > 0 && yval > 0 && xval < size && yval < size) {
            return curBuild;
        }
    }
    return NULL;
}

//selects a unit or building based on mouse click position
void selectEntity(int x, int y) {
    unit *curUnit = firstUnit;
    while(curUnit->unitAfter != NULL) {
        curUnit = curUnit->unitAfter;
        int size = curUnit->size;
        int xval = x - curUnit->x;
        int yval = y - curUnit->y;
        if(xval > 0 && yval > 0 && xval < size && yval < size) {
            activeUnit = curUnit;
            activeBuilding = NULL;
            return;
        }
    }
    building *curBuild = firstBuilding;
    while(curBuild->buildingAfter != NULL) {
        curBuild = curBuild->buildingAfter;
        int size = curBuild->size;
        int xval = x - curBuild->x;
        int yval = y - curBuild->y;
        if(xval > 0 && yval > 0 && xval < size && yval < size) {
            activeUnit = NULL;
            activeBuilding = curBuild;
            return;
        }
    }
}

//reads controls, run every game cycle
//returns one if user input indicates game must close
short runEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                return 1;
                break;
            case SDL_MOUSEBUTTONDOWN: ;
                int mousex, mousey, camX, camY, posx, posy;
                SDL_GetMouseState(&mousex, &mousey);
                getCamLoc(&camX, &camY);
                posx = globalPos(mousex, camX);
                posy = globalPos(mousey, camY);
                if(event.button.button == SDL_BUTTON_LEFT) {
                    selectEntity(posx, posy);
                    break;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    unit* selUnit = checkClickUnit(posx, posy);
                    if(selUnit == NULL) {
                        building* selBuild = checkClickBuilding(posx, posy);
                        if(selBuild == NULL) {
                            moveUnitTo(posx, posy);
                        }
                        else{setAttackBuild(selBuild);
                        }
                    }
                    else {
                        setAttack(selUnit);
                    }

            }
        }
    }
}

//checks keyboard state and acts accordingly
short keyboardState() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        return 1;
    }
    if(state[SDL_SCANCODE_UP]) {
        moveCamy(-camSpeed);
    }
    if(state[SDL_SCANCODE_DOWN]) {
        moveCamy(camSpeed);
    }

    if(state[SDL_SCANCODE_LEFT]) {
        moveCamx(-camSpeed);
    }
    if(state[SDL_SCANCODE_RIGHT]) {
        moveCamx(camSpeed);
    }
    if(state[SDL_SCANCODE_Q]) {
        Build(0);
    }
    if (state[SDL_SCANCODE_W]) {
        Build(1);
    }
    if (state[SDL_SCANCODE_E]) {
        Build(2);
    }
    if (state[SDL_SCANCODE_R]) {
        Build(3);
    }
    return 0;
}
