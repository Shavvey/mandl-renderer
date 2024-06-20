#include "window.h"

SDL_Window *create_window(const char *title) {
  SDL_Window *window = NULL;
  if (SDL_Init(SDL_INIT_VIDEO > 0)) {
    fprintf(stderr, "SDL could not be initialized! Error: %s\n",
            SDL_GetError());
    exit(EXIT_FAILURE);
  }
  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "Window could not be created! Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  return window;
}
