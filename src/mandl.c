#include "mandl.h"

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

// return a linear map of the change in both of the inputs
double lmap(double x, double input_start, double input_end, double output_start,
            double output_end) {
  if (input_end == input_start) {

    // print out the error, a linear map doesn't work when their is no change
    fprintf(stderr, "Error in l_map(), Cannot Map a value when input_end == "
                    "input_start! \n");
    // just exit of out the program if the lmap can't be completed
    exit(EXIT_FAILURE);

  } else {
    // determine the slope via the change in output per change in input
    double slope = (output_end - output_start) / (input_end - input_start);
    return output_start + slope * (x - input_start);
  }
}

// preforms the color calculation using the number iterations preformed on the
// complex point

uint32_t color_calc(double val, Color_Palette palette) {
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
  red = ((int)lmap(val, 1, 0, 0, palette.contrast * palette.red_bias))
        << (6 * 4); // starts at 0x--FFFFFF
  green = ((int)lmap(val, 1, 0, 0, palette.contrast * palette.green_bias))
          << (4 * 4); // 0xFF--FFFF
  blue = ((int)lmap(val, 1, 0, 0, palette.contrast * palette.blue_bias))
         << (2 * 4); // 0xFFFF--FF
  // alpha won't be map to the number of iterations
  alpha = 0xFF;
  // return the rgba representation of the color
  return (red + green + blue + alpha);
}

// update the pixel buffer according to the new mandl set
void mandl_update(Plot_Window p_win, Color_Palette palette) {
  // extract imaginary coords of plot window
  double istart = p_win.i_start;
  double iend = p_win.i_end;
  // real coords of plot window
  double rstart = p_win.r_start;
  double rend = p_win.r_end;
  double normalized_color = 0;

  for (int dy = 0; dy < DIM.height; dy++) {
    for (int dx = 0; dx < DIM.width; dx++) {
      Complex c;
      // convert pixel coordinates into the complex plot coordinates
      c.real = rstart + ((double)dy / DIM.height) * (rend - rstart);
      c.img = istart + ((double)dx / DIM.width) * (iend - istart);
      uint32_t itrs = mandl_iter(c);
      normalized_color = lmap(itrs, 0, MAX_ITER, 0, 1);
      uint32_t color = color_calc(normalized_color, palette);
      // use RGBA color calculated via the linear mapping between iterations and
      // color strength (darker colors for converge points (ones inside the set)
      // and lighter colors for diverging points (ones not inside the set))
      screen_buffer[dy * WIDTH + dx] = color;
    }
  }
}
