#include "complex.h"
#include <stdint.h>

// describes the default start point when begining to render set
#define RE_START -2
#define RE_END 1
#define IM_START -1
#define IM_END 1

// max number of iterations
#define MAX_ITER 80
#define THRESHOLD 2

// determines what points we sample to construct set
typedef struct Plot_Window {
  double r_start;
  double r_end;
  double i_start;
  double i_end;
} Plot_Window;

typedef struct Color_Bias {
  int rb;
  int gb;
  int bb;
  int coef;
} Color_Bias;

extern Plot_Window PLOT;

uint32_t mandl_iter(Complex c);
void update();
double l_map(double x, double input_start, double input_end,
             double output_start, double output_end);

uint32_t color_calc(double val, int red_bias, int green_bias, int blue_bias,
                    int coef);
