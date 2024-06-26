#include "complex.h"
#include <stdint.h>

// describes the default start point when begining to render set
#define DEF_RE_START -2
#define DEF_RE_END 1
#define DEF_IM_START -1
#define DEF_IM_END 1

// max number of iterations
#define MAX_ITER 80
#define THRESHOLD 2

// determines what points we sample to construct set
typedef struct Plot_Window {
  double r_start;
  double r_end;
  double i_start;
  double i_end;
  double xoff;
  double yoff;
} Plot_Window;

typedef struct Color_Bias {
  int rb;
  int gb;
  int bb;
  int coef;
} Color_Bias;

uint32_t mandl_iter(Complex c);
void mandl_update(Plot_Window p_win);
double lmap(double x, double input_start, double input_end, double output_start,
            double output_end);

uint32_t color_calc(double val, int red_bias, int green_bias, int blue_bias,
                    int coef);
