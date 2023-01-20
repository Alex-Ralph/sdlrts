#include "buildings.h"

//initialises firstBuilding, for the sake of the linked list
void initBuildings() {
    firstBuilding = (building *)malloc(sizeof(building));
    firstBuilding->buildingBefore = NULL;
    firstBuilding->buildingAfter = NULL;
}

//used to assign IDs to buildings
int ID = 0;

//returns a pointer to the last building in the linked list
building *lastBuilding() {
    building *build = firstBuilding;
    while(build->buildingAfter != NULL) {
        build = build->buildingAfter;
    }
    return build;
}

//adds a building to the game at the given coordinates, of the given team and type
void addBuilding(int type, int x, int y, int team) {
    building *newBuilding = (building *)malloc(sizeof(building));
    building *lastInList = lastBuilding();
    newBuilding->buildingBefore = lastInList;
    lastInList->buildingAfter = newBuilding;
    newBuilding->buildingAfter = NULL;
    switch(type) {
        case 0: //the only building type for now
            newBuilding->size = 100;
            newBuilding->health = 800;
            break;
    }

    newBuilding->ID = ID;
    ID++;
    newBuilding->maxhealth = newBuilding->health;
    newBuilding->x = x;
    newBuilding->y = y;
    newBuilding->typeID = type;
    newBuilding->team = team;
    newBuilding->buildTimeRemaining = -1;

}

//removes a building from the game
void removeBuilding(building *toRemove) {
    toRemove->buildingBefore->buildingAfter = toRemove->buildingAfter;
    if(toRemove->buildingAfter != NULL) {
        toRemove->buildingAfter->buildingBefore = toRemove->buildingBefore;
    }
    free(toRemove);
}

//removes all buildings from the game, used when shutting down
void removeAllBuildings() {
    building *build = firstBuilding;
    while(build != NULL) {
        building *nextBuild = build->buildingAfter;
        free(build);
        build = nextBuild;
    }
}

//Begins building of a unit at the selected building, using buildID to tell
//the function what needs to be built
void Build(short buildID) {
    if(activeBuilding != NULL && activeBuilding->buildTimeRemaining <= 0) {
        switch(activeBuilding->typeID) {
            //switch statement based on building type, there can be different
            //logic for different buildings
            case 0:
                switch(buildID) {
                    case 0: //warrior
                        if(removeResources(activeBuilding->team, 100) != 0) {return;}
                        activeBuilding->buildTimeRemaining = 15000;
                        break;
                    case 1: //scout

                        if(removeResources(activeBuilding->team, 50) != 0) {return;}
                        activeBuilding->buildTimeRemaining = 10000;
                        break;
                    case 2: //archer
                        if(removeResources(activeBuilding->team, 100) != 0) {return;}
                        activeBuilding->buildTimeRemaining = 12000;
                        break;
                    case 3: //test unit
                        activeBuilding->buildTimeRemaining=3000;
                }
                activeBuilding->totalBuildTime = activeBuilding->buildTimeRemaining;
                activeBuilding->unitBuildingType = buildID;
                return;
            }
    }
}

//Function responsible for materialisation of the unit at the correct location
void buildUnit(building *build) {
    int depositx = build->size / 2 + build->x;
    int deposity = build->size + build->y;
    addUnit(build->unitBuildingType, depositx, deposity, build->team);
}

//function that returns the map coordinates of the center of the building
void findBuildCenter(building *build, int *x, int *y) {
    *x = (build->size)/2  + build->x;
    *y = (build->size)/2 + build->y;
}

//logic regarding running the buildings for one in-game loop
void buildLogic() {
    building *build = firstBuilding;
    while(build->buildingAfter != NULL) {
        build = build->buildingAfter;
        if(build->health <= 0) {
            removeBuilding(build);
            continue;
        }
        if(build->buildTimeRemaining < 0) {
            continue;
        }
        else if(build->buildTimeRemaining <= 10) {
            build->buildTimeRemaining = -1;
            build->totalBuildTime = -1;
            buildUnit(build);
        }
        else if(build->buildTimeRemaining > 10) {
            build->buildTimeRemaining -= 10;
        }
    }
}
