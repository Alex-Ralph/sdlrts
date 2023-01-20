#ifndef _UNITSTRUCTS_
#define _UNITSTRUCTS_
#include "unitStructs.h"
#endif


#ifndef _STDLIB_
#define _STDLIB_
#include <stdlib.h>
#endif

#ifndef _MATH_
#define _MATH_
#include <math.h>
#endif

#ifndef _PROJECTILES_
#define _PROJECTILES_
#include "projectiles.h"
#endif

#ifndef _BUILDINGS_
#define _BUILDINGS_
#include "buildings.h"
#endif


//Allows for creation of a unit by specification of typeID, returns unitID
short addUnit(short typeID, int x, int y, short team);

//initialises the units linked list
void initUnits();

//removes all units from the linked list
void removeAllUnits();

//Moves a unit a single cycle towards its destination
void moveUnit(unit *curUnit);

//cycles through all logic for a unit
void unitsLogic();

//tells a unit to move to a location
void moveUnitTo(int x, int y);

//checks if a unit exists under the given map location
unit* checkClick(int x, int y);

//tells the active unit to attack another unit
void setAttack(unit *selUnit);

//finds the center of a unit, returned to the two pointers
void findCenter(unit *curUnit, int *inpx, int *inpy);

//sets the active unit to attack the selected building
void setAttackBuild(building *build);
