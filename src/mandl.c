#include "mandl.h"
// construct a basic plot window
const Complex START = {.real = -2, .img = -1};
const Complex END = {.real = 1, .img = 1};
const Plot_Window PLOT = {.start = START, .end = END};

// iterate using complex point given, return total iterations
uint32_t mandl_iter(Complex c) {
  Complex z = {.img = 0, .real = 0};
  uint32_t itrs = 0;
  while (cmabs(z) <= THRESHOLD && itrs < MAX_ITER) {
    Complex z = cmadd(cmsqr(z), c);
    itrs++;
  }
  return itrs;
}
