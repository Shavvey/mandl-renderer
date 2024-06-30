# choice of compiler w/ flags
CC=gcc
FLAGS=-W -Wall -g
# sdl flags and included libs
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
# executable name, object files to be created, and dependencies for object files
EXEC=mandl
OBJS=src/main.o src/window.o src/complex.o src/mandl.o src/thread.o
DEPS=src/window.h src/complex.h src/mandl.h src/thread.h

# make dependencies to create the final executable
all: $(EXEC)

# simplified rule that makes all object files from their header and source
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c  -o $@ $<

# rule to make the final executable from the created object files
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(OBJS) -o $(EXEC) $(SDL_LDFLAGS) -lm

# clean out the object files and the final executable
clean:
	rm $(EXEC) src/*.o
