#include "window.h"
#include <stdbool.h>
#include <stdlib.h>
// store the hardcoded window dimensions
const Window_Dim DIM = {.width = WIDTH, .height = HEIGHT};
uint32_t *screen_buffer;
SDL_Context cxt;

SDL_Window *create_window(const char *title) {
  SDL_Window *window = NULL;
  if (SDL_Init(SDL_INIT_VIDEO > 0)) {
    fprintf(stderr, "SDL could not be initialized! Error: %s\n",
            SDL_GetError());
    exit(EXIT_FAILURE);
  }
  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       DIM.width, DIM.height, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "Window could not be created! Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  return window;
}

SDL_Context get_context(SDL_Window *window) {
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_STREAMING, DIM.width, DIM.height);
  SDL_Context cxt = {.renderer = renderer, .texture = texture};
  return cxt;
}

uint32_t *init_buffer() {
  uint32_t *screen_buffer = malloc(sizeof(uint32_t) * DIM.width * DIM.height);
  memset(screen_buffer, 0xFF, DIM.width * DIM.height * sizeof(uint32_t));
  return screen_buffer;
}
void cleanup() {
  // destroy SDL context (renderer and texture) if they exist
  if (cxt.texture) {
    SDL_DestroyTexture(cxt.texture);
  }
  if (cxt.renderer) {
    SDL_DestroyRenderer(cxt.renderer);
  }
  // free up screen buffer and quit out of window
  free(screen_buffer);
  SDL_Quit();
}

void animate() {
  bool ended = false;
  SDL_Event event;
  while (!ended) {
    // update texture with the new mandlbrot set computed
    SDL_UpdateTexture(cxt.texture, NULL, screen_buffer,
                      DIM.width * sizeof(uint32_t));
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDLK_ESCAPE:
        ended = true;
        break;
      case SDL_QUIT:
        ended = true;
        break;

      default:
        // no nothing by default
        break;
      }
    }
    // clear current render
    SDL_RenderClear(cxt.renderer);
    // copy new texture over
    SDL_RenderCopy(cxt.renderer, cxt.texture, NULL, NULL);
    // present new render
    SDL_RenderPresent(cxt.renderer);
  }
  // cleanup process
  cleanup();
}
