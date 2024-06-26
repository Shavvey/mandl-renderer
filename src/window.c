#include "window.h"
#include "mandl.h"
#include <stdbool.h>
#include <stdlib.h>

const Window_Dim DIM = {.width = WIDTH, .height = HEIGHT};
uint32_t screen_buffer[WIDTH][HEIGHT] = {0xFF};
SDL_Context cxt;
bool window_exit = false;
SDL_Event event;
int mouse_x, mouse_y;
// controls the window of the plotting region
Plot_Window P_WIN = {.r_start = DEF_RE_START,
                     .r_end = DEF_RE_END,
                     .i_start = DEF_IM_START,
                     .i_end = DEF_IM_END};

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
  // check to see if window is created successfully
  if (window == NULL) {
    fprintf(stderr, "Window could not be created! Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  return window;
}

SDL_Context get_context(SDL_Window *window) {
  // create renderer from window
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // create the sdl context, which stores the current render and it's texture
  SDL_Context cxt = {.renderer = renderer,
                     .texture = SDL_CreateTexture(
                         renderer, SDL_PIXELFORMAT_RGBA8888,
                         SDL_TEXTUREACCESS_STREAMING, DIM.width, DIM.height)};
  return cxt;
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
  SDL_Quit();
}

void handle_event() {
  switch (event.type) {
  case SDLK_ESCAPE:
    window_exit = true;
    break;
  case SDL_QUIT:
    window_exit = true;
    break;
  case SDL_MOUSEBUTTONDOWN:
    // get the mouse x and y (top left of screen is the origin)
    SDL_GetMouseState(&mouse_x, &mouse_y);
    // shift mouse coords so zero corresponds to center
    mouse_x -= (WIDTH / 2);
    mouse_y -= (HEIGHT / 2);
    // starting coords by offset
    double xoff = ((double)mouse_x / WIDTH) * (P_WIN.i_end - P_WIN.i_start);

    double yoff = ((double)mouse_y / HEIGHT) * (P_WIN.r_end - P_WIN.r_start);
    // use offset to change plot window coords
    // NOTE: imaginary coords are on the x-axis here
    P_WIN.r_start += yoff;
    P_WIN.r_end += yoff;
    P_WIN.i_start += xoff;
    P_WIN.i_end += xoff;
    // update using new plot window
    mandl_update(P_WIN);
    break;
  default:
    // no nothing by default
    break;
  }
}

void center(Plot_Window *p_win, int mouse_x, int mouse_y) {}

void zoom(Plot_Window *p_win, int mouse_x, int mouse_y, int scalar) {}

void animate() {
  // create the mandelbrot set using default plot window P_WIN
  mandl_update(P_WIN);
  while (!window_exit) {
    // update texture with the new mandlbrot set computed
    SDL_UpdateTexture(cxt.texture, NULL, screen_buffer,
                      DIM.width * sizeof(uint32_t));

    while (SDL_PollEvent(&event)) {

      // handle any key press
      handle_event();
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
