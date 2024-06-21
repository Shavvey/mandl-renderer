#include "complex.h"
#include <stdint.h>

// max number of iterations
#define MAX_ITER 80
#define THRESHOLD 2
// determines what points we sample to construct set
typedef struct Plot_Window {
  Complex start;
  Complex end;
} Plot_Window;

typedef struct Mandl_Set {
  // mandl set is just an array of complex points
  Complex *set_arr;
} Mandl_Set;

uint32_t mandl_iter(Complex c);
