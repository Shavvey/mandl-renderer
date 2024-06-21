#include <math.h>
#include <stdbool.h>

// struct used to create a complex number
typedef struct Complex {
  double real; // real part
  double img;  // imaginary part
} Complex;

Complex cmadd(Complex a, Complex b);
double cmabs(Complex c);
Complex cmsqr(Complex c);
