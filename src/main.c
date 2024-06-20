#include "window.h"

int main(int argc, char *argv[]) {
  SDL_Window *window = create_window("Mandelbrot Renderer");
  cxt = get_context(window);
  screen_buffer = init_buffer();
  animate();
  return EXIT_SUCCESS;
}
