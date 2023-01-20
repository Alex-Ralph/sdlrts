/*projectiles.c contains logic regarding creation and destruction of
projectiles, their direction and speed of travel, and whether they damage
a unit, as well as a function to keep projectiles updated every
game loop.
*/

#ifndef _UNITSTRUCTS_
#define _UNITSTRUCTS_
#include "unitStructs.h"
#endif

#ifndef _UNITS_
#define _UNITS_
#include "units.h"
#endif

#ifndef _MATH_
#define _MATH_
#include <math.h>
#endif

//initialises the first projectile, must be run at start
void initProjectiles();

//cycles through projectiles to keep them updated
void cycleProjectiles();

//adds a projectile at the specified source unit, returns its pointer
projectile *addProjectile(unit *source);

//removes all projectiles, used on shutdown
void removeAllProjectiles();
