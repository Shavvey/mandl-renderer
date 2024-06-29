#ifndef MANDL_H
#define MANDL_H
#include "complex.h"
#include "window.h"
#include <stdint.h>

// describes the default start point when begining to render set
#define DEF_RE_START -2
#define DEF_RE_END 1
#define DEF_IM_START -1
#define DEF_IM_END 1

// max number of iterations
#define MAX_ITER 80
#define THRESHOLD 2

typedef struct Color_Bias {
  int rb;
  int gb;
  int bb;
  int coef;
} Color_Bias;

uint32_t mandl_iter(Complex c);
void mandl_update(Plot_Window p_win, Color_Palette palette);
double lmap(double x, double input_start, double input_end, double output_start,
            double output_end);

uint32_t color_calc(double val, Color_Palette palette);
#endif // !MANDL_H
