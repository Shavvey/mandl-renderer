#include "window.h"
#include "mandl.h"
#include "thread.h"
#include <stdbool.h>
#include <stdlib.h>
// window dimensions of the screen
const Window_Dim DIM = {.width = WIDTH, .height = HEIGHT};
// buffer to create texture and renderer for each frame
uint32_t *screen_buffer;
// sdl context just stores the renderer and texturer used in each frame
SDL_Context cxt;
bool window_exit = false;
SDL_Event event;
int mouse_x, mouse_y;
#define ZOOMFAC 0.7
// controls the window of the plotting region
Plot_Window plot_window = {.r_start = DEF_RE_START,
                           .r_end = DEF_RE_END,
                           .i_start = DEF_IM_START,
                           .i_end = DEF_IM_END};
// color pallete, controls colors of the mandelbrot set
Color_Palette palette = {
    .red_bias = 50, .green_bias = 50, .blue_bias = 50, .contrast = 1};

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

// context just stores the current renderer and texturer
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

// initialize the screen buffer, memory is stored on the heap so that it can be
// acessed by child threads
void init_screen() {
  screen_buffer = (uint32_t *)malloc(sizeof(uint32_t) * WIDTH * HEIGHT);
  // initializing each pixel stored in the buffer to be white
  memset(screen_buffer, 0xFFFFFFFF, WIDTH * HEIGHT * sizeof(uint32_t));
}

// function to handle cleanup of heap allocations and sdl objects on exit
void cleanup() {
  // destroy SDL context (renderer and texture) if they exist
  if (cxt.texture) {
    SDL_DestroyTexture(cxt.texture);
  }
  if (cxt.renderer) {
    SDL_DestroyRenderer(cxt.renderer);
  }
  // free dynamic allocations (threads info and screen_buffer)
  free(screen_buffer);
  free(threads);
  // get rid of the window
  SDL_Quit();
}

void handle_event() {
  switch (event.type) {
  case SDL_QUIT:
    window_exit = true;
    break;
  case SDL_MOUSEBUTTONDOWN:
    // get the mouse x and y (top left of screen is the origin)
    SDL_GetMouseState(&mouse_x, &mouse_y);
    center(&plot_window, mouse_x, mouse_y);
    // update using new plot window
    th_update();
    break;

  // if a key has been pressed down handle that key
  case SDL_KEYDOWN:

    switch (event.key.keysym.sym) {
    case SDLK_z:
      // printf("Zooming..\n");
      zoom(&plot_window, mouse_x, mouse_y, ZOOMFAC);
      th_update();
      break;

    case SDLK_r:
      palette.red_bias += 10;
      th_update();
      break;

    case SDLK_b:
      palette.blue_bias += 10;
      th_update();
      break;

    case SDLK_g:
      palette.green_bias += 10;
      th_update();
      break;

    case SDLK_c:
      palette.contrast += 5;
      th_update();
      break;
    }

    break;
  default:
    // no nothing by default
    break;
  }
}

void center(Plot_Window *p_win, int mouse_x, int mouse_y) {
  // shift mouse coords so zero corresponds to center
  mouse_x -= (WIDTH / 2);
  mouse_y -= (HEIGHT / 2);
  // get offset in terms of the complex plotting coordinates
  double xoff = ((double)mouse_x / WIDTH) * (p_win->i_end - p_win->i_start);
  double yoff = ((double)mouse_y / HEIGHT) * (p_win->r_end - p_win->r_start);
  // use offset to shift plotting coordinates
  p_win->r_start += yoff;
  p_win->r_end += yoff;
  p_win->i_end += xoff;
  p_win->i_start += xoff;
}

void zoom(Plot_Window *p_win, int mouse_x, int mouse_y, double scalar) {
  // scale the plot window via the scalar
  p_win->r_start *= scalar;
  p_win->r_end *= scalar;
  p_win->i_end *= scalar;
  p_win->i_start *= scalar;
  center(p_win, mouse_x, mouse_x);
}

void animate() {
  init_threads();
  th_update();
  // create the mandelbrot set using default plot window P_WIN
  while (!window_exit) {
    // update texture with the new mandlbrot set computed
    SDL_UpdateTexture(cxt.texture, NULL, screen_buffer,
                      DIM.width * sizeof(uint32_t));

    while (SDL_PollEvent(&event)) {
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
