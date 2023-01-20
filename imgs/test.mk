objects = unitStructs.h  SDLRendering.o unitTests.o controls.o
CFLAGS := $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs)

unitTests: $(objects)
	gcc $(objects) $(CFLAGS) $(LDFLAGS) -lpthread -lSDL2_image -o test
