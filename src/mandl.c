#include "mandl.h"
#include "window.h"

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
double lmap(double x, double input_start, double input_end, double output_start,
            double output_end) {
  if (input_end == input_start) {

    printf("Error in l_map(), Cannot Map a value when input_end == "
           "input_start! \n");
    exit(EXIT_FAILURE);

  } else {
    // determine the slope via the change in output per change in input
    double slope = (output_end - output_start) / (input_end - input_start);
    return output_start + slope * (x - input_start);
  }
}
uint32_t color_calc(double val, int red_bias, int green_bias, int blue_bias,
                    int coef) {
  // check normalized val should have a interval [0,1]
  if ((val < 0.0) | (val > 1.0)) {
    fprintf(stderr, "Error calcuating color val: should be normalized!\n");
    exit(EXIT_FAILURE);
  }
  // init colors
  uint32_t red = 0;
  uint32_t green = 0;
  uint32_t blue = 0;
  uint32_t alpha = 0xFF;
  // each hexadecimal digit represents a half-byte (4 bits)
  red = ((int)lmap(val, 1, 0, 0, coef * red_bias))
        << (6 * 4); // starts as 0x--FFFFFF
  green = ((int)lmap(val, 1, 0, 0, coef * green_bias)) << (4 * 4); // 0xFF--FFFF
  blue = ((int)lmap(val, 1, 0, 0, coef * blue_bias)) << (2 * 4);   // 0xFFFF--FF
  // alpha won't be map to the number of iterations
  alpha = 0xFF;

  return (red + green + blue + alpha);
}
// update the pixel buffer according to the new mandl set
void update() {
  // imaginary coords of plot window
  double istart = -1;
  double iend = 1;
  // real coords of plot window
  double rstart = -2;
  double rend = 1;
  double normalized_color = 0;

  for (int dx = 0; dx < DIM.width; dx++) {
    for (int dy = 0; dy < DIM.height; dy++) {
      Complex c;
      c.real = rstart + ((double)dx / DIM.width) * (rend - rstart);
      c.img = istart + ((double)dy / DIM.height) * (iend - istart);
      uint32_t itrs = mandl_iter(c);
      normalized_color = lmap(itrs, 0, MAX_ITER, 0, 1);
      uint32_t color = color_calc(normalized_color, 50, 50, 50, 1);
      // RGBA
      screen_buffer[dx][dy] = color;
    }
  }
}
