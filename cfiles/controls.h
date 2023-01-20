/*controls.c contains the functions that read
user input and convert it into useful commands for the rest
of the game. The majority of methods in controls.c are accessible
only to controls.c*/

#ifndef _SDLLIBS_
#define _SDLLIBS_
#include<SDL.h>
#include<SDL_image.h>
#endif

#ifndef _SDLRENDERING_
#define _SDLRENDERING_
#include "SDLRendering.h"
#endif


#ifndef _UNITS_
#define _UNITS_
#include "units.h"
#endif

#ifndef _BUILDINGS_
#define _BUILDINGS_
#include "buildings.h"
#endif

//both of these functions must be called once per game cycle, to check and
//react to new user input
short runEvents();
short keyboardState();
