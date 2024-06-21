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
  Complex start;
  Complex end;
} Plot_Window;

extern Plot_Window PLOT;

uint32_t mandl_iter(Complex c);
void update();
