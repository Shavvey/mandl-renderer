#include "window.h"

int main(int argc, char *argv[]) {
  SDL_Window *window = create_window("Mandelbrot Renderer");
  init_screen();
  cxt = get_context(window);
  animate();
  return EXIT_SUCCESS;
}
