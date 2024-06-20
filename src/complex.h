#include <math.h>
#include <stdbool.h>
#include <stdint.h>

// struct used to create a complex number
typedef struct Complex {
  double real; // real part
  double img;  // imaginary part
} Complex;

// describe each point in mandlbrot set
typedef struct Complex_Point {
  Complex val;   // val the complex point represents
  bool in_set;   // whether point is in set or not
  uint32_t itrs; // number of iterations done on this point
} Complex_Point;

typedef struct Mandl_Set {
  // mandl set is just an array of complex points
  Complex_Point *set;
} Mandl_Set;

Complex cmadd(Complex a, Complex b);
void cmset(Complex *c, Complex n);
double cmabs(Complex c);
