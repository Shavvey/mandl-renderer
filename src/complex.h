#include <math.h>
#include <stdbool.h>

typedef struct Complex {
  double real;
  double img;
} Complex;
// describe each point in mandlbrot set
typedef struct Complex_Point {
  Complex sum;
  Complex product;
  Complex abs;
  bool in_set;
} Complex_Point;

Complex cadd(Complex a, Complex b);
void cset(Complex *c, double real, double img);
double cabs(Complex c);
Complex csqr(Complex a);
