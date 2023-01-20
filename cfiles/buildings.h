/*buildings.h contains all logic pertaining to buildings,
their construction, removal, the construction of units,
as well as containing a loop tha must be run every game cycle
which looks after each building's state every tick
*/

#ifndef _SDLLIBS_
#define _SDLLIBS_
#include<SDL.h>
#include<SDL_image.h>
#endif

#ifndef _UNITSTRUCTS_
#define _UNITSTRUCTS_
#include "unitStructs.h"
#endif

#ifndef _UNITS_
#define _UNITS_
#include "units.h"
#endif

#ifndef _RESOURCES_
#define _RESOURCES_
#include "resources.h"
#endif

void Build(short buildID);

//initialises firstBuilding, for the sake of the linked list
void initBuildings();

//adds a building to the game at the given coordinates, of the given team and type
void addBuilding(int type, int x, int y, int team);

//removes all buildings from the game, used when shutting down
void removeAllBuildings();

//logic regarding running the buildings for one in-game loop
void buildLogic();

//function that returns the map coordinates of the center of the building
void findBuildCenter(building *build, int *x, int *y);
