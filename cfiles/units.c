#include "units.h"
#include<stdio.h>
//for assigning unit IDs. Is incremented by one every time a unit ID is assigned
short curID = 0;

//To store the currently selected (active) unit

//creates an empty first unit, to serve as the starting point of the linked list
void initUnits() {
    firstUnit = (unit *)malloc(sizeof(unit));
    firstUnit->unitBefore = NULL;
    firstUnit->unitAfter = NULL;
    initProjectiles();
    initBuildings();

}

//returns the last unit in the linked list
unit *lastInList() {
    if(firstUnit->unitAfter == NULL) {
        return firstUnit;
    }
    unit *nextUnit = firstUnit->unitAfter;
    while(1) {
        if(!(nextUnit->unitAfter)) {
            return nextUnit;
        }
        else {
            nextUnit = nextUnit->unitAfter;
        }
    }

}

//adds a blank unit to the linked list
unit *createBlankUnit() {
    unit *theUnit = (unit *)malloc(sizeof(unit));
    unit *last = lastInList();
    last->unitAfter = theUnit;
    theUnit->unitBefore = last;
    theUnit->unitAfter = NULL;
    theUnit->ID = curID;
    curID++;
    return theUnit;
}

//adds a given unit to the map
short addUnit(short typeID, int x, int y, short team) {
    unit *addedUnit = createBlankUnit();
    switch(typeID) {
        case 0: //warrior
        addedUnit->typeID = 0;
        addedUnit->maxhealth = 100;
        addedUnit->atk = 12;
        addedUnit->atkspd = 1300;
        addedUnit->movSpd = 100;
        addedUnit->range = 0;
        addedUnit->size = 50;
        break;

        case 1: //scout
        addedUnit->typeID = 1;
        addedUnit->maxhealth = 100;
        addedUnit->atk = 7;
        addedUnit->atkspd = 1000;
        addedUnit->movSpd = 220;
        addedUnit->range = 0;
        addedUnit->size = 45;
        break;

        case 2: //archer
        addedUnit->typeID = 2;
        addedUnit->maxhealth = 40;
        addedUnit->atk = 7;
        addedUnit->atkspd = 750;
        addedUnit->movSpd = 170;
        addedUnit->range = 400;
        addedUnit->size = 30;
        break;

        case 3: //ridiculously overpowered test unit
        addedUnit->typeID=3;
        addedUnit->maxhealth = 4000;
        addedUnit->atk = 200;
        addedUnit->atkspd = 4000;
        addedUnit->movSpd = 80;
        addedUnit->range = 0;
        addedUnit->size = 100;

    }
    addedUnit->health = addedUnit->maxhealth;
    addedUnit->x = x;
    addedUnit->y = y;
    addedUnit->realX = x;
    addedUnit->realY = y;

    addedUnit->moveToX = -1;
    addedUnit->moveToY = -1;
    addedUnit->team = team;
    addedUnit->attacking = NULL;
    addedUnit->timeToAtk = 0;
    addedUnit->attackingBuilding = NULL;
}

//removes the given unit from the linked list
void removeUnit(unit *toRemove) {
    unit *unitBefore = toRemove->unitBefore;
    unit *unitAfter = toRemove->unitAfter;
    if(unitAfter != NULL) {
        unitAfter->unitBefore =unitBefore;
    }
    unitBefore->unitAfter = unitAfter;
    free(toRemove);
}

//deletes all units, used in shutdown
void removeAllUnits() {
    unit *nextUnit;
    unit *curUnit = firstUnit;
    while(curUnit->unitAfter != NULL) {
        nextUnit = curUnit->unitAfter;
        free(curUnit);
        curUnit=nextUnit;
    }
    free(curUnit);
}

//moves a unit one cycle's worth of distance towards the given parameters
void moveToCoords(unit *curUnit, int x, int y) {
    float movSpd = (float)curUnit->movSpd / 100.0;
    float distX = (float)x - curUnit->realX;
    float distY = (float)y - curUnit->realY;
    if(fabs(distX) + fabs(distY) < movSpd) {
        curUnit->x = x;
        curUnit->y = y;
        curUnit->realX = x;
        curUnit->realY = y;
        curUnit->moveToX = -1;
        curUnit->moveToY = -1;
        return;
    }
    //works out how far to travel in the x and y directions if target is out of range
    else {
        float travelX = (movSpd * distX) / (fabs(distX) + fabs(distY));
        float travelY = ((float)movSpd - fabs(travelX)) * ((distY > 0) - (distY < 0));
        curUnit->realX += travelX;
        curUnit->realY += travelY;
        curUnit->x = (int)curUnit->realX;
        curUnit->y = (int)curUnit->realY;
    }
}


//moves a unit one game cycle's worth of distance towards its targets
void moveUnit(unit *curUnit) {
    moveToCoords(curUnit, curUnit->moveToX, curUnit->moveToY);
}



//sets the active unit's destination to the parameters given
//as unit coordinates are stored from the top left, this function also converts
//a command so that the middle of the unit will end up at the parameters
//rather than the top
void moveUnitTo(int x, int y) {
    if(activeUnit != NULL && x > 0 && y > 0) {
        activeUnit->attacking = NULL;
        activeUnit->attackingBuilding = NULL;
        activeUnit->realX = activeUnit->x;
        activeUnit->realY = activeUnit->y;
        int size = activeUnit->size;
        int adjustment = size / 2;
        activeUnit->moveToX = x - adjustment;
        activeUnit->moveToY = y - adjustment;
    }
}


//sets the active unit to attack the selected unit
void setAttack(unit *selUnit) {
    if(activeUnit->team != selUnit->team && activeUnit != selUnit) {
        activeUnit->attacking = selUnit;
        activeUnit->attackingBuilding = NULL;
        activeUnit->moveToX = -1;
        activeUnit->moveToY = -1;
    }
}

//sets the active unit to attack the given building
void setAttackBuild(building *build) {
    if(activeUnit->team != build->team) {
        activeUnit->attackingBuilding = build;
        activeUnit->attacking = NULL;
        activeUnit->moveToX = -1;
        activeUnit->moveToY = -1;
    }
}

//returns the center of a unit
void findCenter(unit *curUnit, int *inpx, int *inpy) {
    *inpx = curUnit->x + (curUnit->size)/2;
    *inpy = curUnit->y + (curUnit->size)/2;
}

//logic for one unit to attack another
void attackUnit(unit *unitAttacking) {
    unit *unitAttacked = unitAttacking->attacking;
    int attackingx, attackingy, attackedx, attackedy;
    int distance, distx, disty;
    findCenter(unitAttacking, &attackingx, &attackingy);
    findCenter(unitAttacked, &attackedx, &attackedy);
    distx = abs(attackingx - attackedx);
    disty = abs(attackingy - attackedy);
    distance = sqrt(distx*distx + disty*disty);

    //if in range
    if(distance <
    unitAttacking->size/2 + unitAttacked->size/2 + unitAttacking->range) {
        if(unitAttacked->attacking == NULL &&
            unitAttacked->attackingBuilding == NULL &&
            unitAttacked->moveToX == -1 && unitAttacked->moveToY == -1) {
            unitAttacked->attacking = unitAttacking;
        }
        if(unitAttacking->range ==0) { //melee unit
            if(unitAttacking->timeToAtk <= 0) {
                unitAttacked->health -= unitAttacking->atk;
                unitAttacking->timeToAtk = unitAttacking->atkspd;
                if(unitAttacked->health <= 0) {
                    unitAttacking->attacking = NULL;
                }
            }
        }
        else { //ranged unit
            if(unitAttacked->health <= 0) {
                unitAttacking->attacking = NULL;
                return;
            }
            if(unitAttacking->timeToAtk <= 0) {
                addProjectile(unitAttacking);
                unitAttacking->timeToAtk = unitAttacking->atkspd;
            }
        }
    }
    else {
        moveToCoords(unitAttacking, unitAttacked->x, unitAttacked->y);
    }
}

//moves a unit one cycle towards its goal of attacking its target building
void attackBuilding(unit *unitAttacking) {
    building *build = unitAttacking->attackingBuilding;
    int attackingx, attackingy, attackedx, attackedy;
    int distance, distx, disty;
    findCenter(unitAttacking, &attackingx, &attackingy);
    findBuildCenter(build, &attackedx, &attackedy);
    distx = abs(attackingx - attackedx);
    disty = abs(attackingy - attackedy);
    distance = sqrt(distx*distx + disty*disty);
    //only melee attacks on buildings
    if(distance <=
    (unitAttacking->size + build->size)/2) {
        if(unitAttacking->timeToAtk <= 0) {
            build->health -= unitAttacking->atk;
            unitAttacking->timeToAtk = unitAttacking->atkspd;
            if(build->health <= 0) {
                unitAttacking->attackingBuilding = NULL;
            }
        }
    }
    else {
        moveToCoords(unitAttacking, attackedx, attackedy);
    }
}

//to be run every cycle. Moves, attacks, etc. each unit in turn
void unitsLogic() {
    unit *curUnit = firstUnit;
    while(curUnit->unitAfter != NULL) {
        curUnit = curUnit->unitAfter;
        if(curUnit->health <= 0) {
            unit *tempUnit = curUnit->unitBefore;
            removeUnit(curUnit);
            curUnit = tempUnit;
            continue;
        }
        if(curUnit->attacking != NULL) {
            attackUnit(curUnit);
        }
        else if(curUnit->attackingBuilding != NULL) {
            attackBuilding(curUnit);
        }
        else if(curUnit->moveToX > 0 || curUnit->moveToY > 0) {
            moveUnit(curUnit);
        }

        if(curUnit->timeToAtk > 0) {
            curUnit->timeToAtk -= 10;
        }
    }

}
