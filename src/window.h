#include "sdl.h"
#define WIDTH 1000
#define HEIGHT 1000
#define NANO_PER_SEC 1000000000.0

typedef struct Window_Dim {
  int width;
  int height;
} Window_Dim;

typedef struct SDL_Context {
  SDL_Renderer *renderer;
  SDL_Texture *texture;
} SDL_Context;

typedef struct Color {
  int red_bias;
  int blue_bias;
  int green_bias;
} Color;

// external var needed for other files (such as complex.c)
extern uint32_t *screen_buffer;
extern SDL_Context cxt;

SDL_Window *create_window(const char *title);
SDL_Context get_context(SDL_Window *window);
uint32_t *init_buffer();
void animate();
void cleanup();
