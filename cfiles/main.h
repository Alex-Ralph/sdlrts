/*Functions within main involve around setting up the game
and running the different loops in different threads to
keep it running, as well as shutting down the game at the end*/

#ifndef _SDLLIBS_
#define _SDLLIBS_
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#endif

#ifndef _IOLIBS_
#define _IOLIBS_
#include<stdio.h>
#endif

#ifndef _UNITSTRUCTS_
#define _UNITSTRUCTS_
#include "unitStructs.h"
#endif

#ifndef _SDLRENDERING_
#define _SDLRENDERING_
#include "SDLRendering.h"
#endif

#ifndef _PTHREAD_
#define _PTHREAD_
#include <pthread.h>
#endif

#ifndef _CONTROLS_
#define _CONTROLS_
#include "controls.h"
#endif

#ifndef _UNITS_
#define _UNITS_
#include "units.h"
#endif

#ifndef _BUILDINGS_
#define _BUILDINGS_
#include "buildings.h"
#endif
