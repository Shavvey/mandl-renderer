#include "mandl.h"
#include "window.h"

// construct a basic plot window
Plot_Window PLOT = {.start = {.real = RE_START, .img = IM_START},
                    .end = {.real = RE_START, .img = IM_END}};
// iterate using complex point given, return total iterations
uint32_t mandl_iter(Complex c) {
  Complex z = {.img = 0, .real = 0};
  uint32_t itrs = 0;
  while (cmabs(z) <= THRESHOLD && itrs < MAX_ITER) {
    Complex sz = cmsqr(z);
    z = cmadd(sz, c);
    itrs++;
  }
  return itrs;
}

// update the pixel buffer according to the new mandl set
void update() {
  Complex c;
  // imaginary coords of plot window
  double istart = PLOT.start.img;
  double iend = PLOT.end.img;
  // real coords of plot window
  double rstart = PLOT.start.real;
  double rend = PLOT.end.real;

  for (int dx = 0; dx < DIM.width; dx++) {
    for (int dy = 0; dy < DIM.height; dy++) {

      c.real = rstart + ((double)dx / DIM.width) * (rend - rstart);
      c.img = istart + ((double)dy / DIM.height) * (iend - istart);
      uint32_t itrs = mandl_iter(c);
      uint32_t color = 0xFFFFFFFF - (int)(itrs * 0xFFFFFFFF / MAX_ITER);

      screen_buffer[dx][dy] = 0;
    }
  }
}
