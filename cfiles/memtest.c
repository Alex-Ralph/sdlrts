//a short file, basically made to show that SDL supposedly leaks a lot
//of memory, regardless as to what one actually does within it
#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include<stdlib.h>

void main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Delay(5000);
    SDL_Quit();
}
