#ifndef WINDOW_H
#define WINDOW_H
#include "sdl.h"
#include "stdbool.h"
#define WIDTH 800
#define HEIGHT 800
#define NANO_PER_SEC 1000000000.0

// struct to store to dimensions of the renderer window
typedef struct Window_Dim {
  int width;
  int height;
} Window_Dim;

// struct to store current render and texture
typedef struct SDL_Context {
  SDL_Renderer *renderer;
  SDL_Texture *texture;
} SDL_Context;

// determines what points we sample to construct set
typedef struct Plot_Window {
  double r_start;
  double r_end;
  double i_start;
  double i_end;
  bool is_dirty;
} Plot_Window;

// color pallette determines iteration colors
typedef struct Color_Palette {
  int red_bias;
  int blue_bias;
  int green_bias;
  int contrast;
} Color_Palette;

// external var needed for other files (such as complex.c and main.c)

extern SDL_Context cxt;
extern const Window_Dim DIM;
extern Plot_Window plot_window;
extern uint32_t *screen_buffer;
extern Color_Palette palette;

SDL_Window *create_window(const char *title);
SDL_Context get_context(SDL_Window *window);
void animate();
void cleanup();
void handle_event();
void center(Plot_Window *p_win, int mouse_x, int mouse_y);
void zoom(Plot_Window *p_win, int mouse_x, int mouse_y, double scalar);
void init_screen();
#endif
