# choice of compiler w/ flags
CC=gcc
FLAGS=-W -Wall -g
# sdl flags and included libs
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs) -lm
EXEC=mandl

# make dependencies to create the final executable
all: mandl

window.o: src/window.c src/window.h  
	$(CC) $(CFLAGS)  -c src/window.c src/window.h

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c 
	

mandl: src/main.o src/window.o
	$(CC) $(CFLAGS) $(SDL_CFLAGS) src/main.o src/window.o -o $(EXEC) $(SDL_LDFLAGS) 
