#include "window.h"

int main(int argc, char *argv[]) {
  SDL_Window *window = create_window("mandl renderer");
  SDL_Context cxt = get_context(window);
  return EXIT_SUCCESS;
}
