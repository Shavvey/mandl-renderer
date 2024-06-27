#ifndef WINDOW_H
#define WINDOW_H
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

// determines what points we sample to construct set
typedef struct Plot_Window {
  double r_start;
  double r_end;
  double i_start;
  double i_end;
} Plot_Window;

typedef struct Color {
  int red_bias;
  int blue_bias;
  int green_bias;
  int contrast;
} Color;

// external var needed for other files (such as complex.c and main.c)

extern SDL_Context cxt;
extern const Window_Dim DIM;
extern uint32_t screen_buffer[WIDTH][HEIGHT];

SDL_Window *create_window(const char *title);
SDL_Context get_context(SDL_Window *window);
void animate();
void cleanup();
void handle_event();
void center(Plot_Window *p_win, int mouse_x, int mouse_y);
void zoom(Plot_Window *p_win, int mouse_x, int mouse_y, double scalar);
#endif
