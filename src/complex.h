#include <math.h>
#include <stdbool.h>

typedef struct Complex {
  double real; // real part
  double img;  // imaginary part
} Complex;

// describe each point in mandlbrot set
typedef struct Complex_Point {
  Complex sum;
  Complex product;
  Complex abs;
  bool in_set;
} Complex_Point;

Complex cmadd(Complex a, Complex b);
void cmset(Complex *c, double real, double img);
double cmabs(Complex c);
