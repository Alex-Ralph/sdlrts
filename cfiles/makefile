objects = unitStructs.h  units.o projectiles.o buildings.o  SDLRendering.o controls.o resources.o
CFLAGS := $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs)

main: $(objects) main.o
	gcc $(objects) main.o $(CFLAGS) $(LDFLAGS) -lpthread -lSDL2_image -lSDL2_ttf -lm -g -o game

prototype1tests: $(objects) prototype1tests.o
		gcc $(objects) prototype1tests.o $(CFLAGS) $(LDFLAGS) -lpthread -lSDL2_image -lSDL2_ttf -lm -g -o test1

prototype2tests: $(objects) prototype2tests.o
		gcc $(objects) prototype2tests.o $(CFLAGS) $(LDFLAGS) -lpthread -lSDL2_image -lSDL2_ttf -lm -g -o test2

memtest: memtest.o
	gcc memtest.o $(CFLAGS) $(LDFLAGS) -lm -g -o memtest
