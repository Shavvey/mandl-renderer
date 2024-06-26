# choice of compiler w/ flags
CC=gcc
FLAGS=-W -Wall -g
# sdl flags and included libs
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
# executable name, object files to be created, and dependencies for object files
EXEC=mandl
OBJS=src/main.o src/window.o src/complex.o src/mandl.o
DEPS=src/window.h src/complex.h src/mandl.h

# make dependencies to create the final executable
all: mandl

# simplified rule that makes all object files from their header and source
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c  -o $@ $<

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(OBJS) -o $(EXEC) $(SDL_LDFLAGS) -lm

clean:
	rm mandl src/*.o
