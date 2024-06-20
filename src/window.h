#include "sdl.h"
#define WIDTH 1000
#define HEIGHT 1000

typedef struct Window_Dim {
  int width;
  int height;
} Window_Dim;

typedef struct SDL_Context {
  SDL_Renderer *renderer;
  SDL_Texture *texture;
} SDL_Context;

SDL_Window *create_window(const char *title);
SDL_Context get_context(SDL_Window *window);
