#include "complex.h"

Complex cmadd(Complex a, Complex b) {
  // just add respective real and imaginary parts of the two numbers
  Complex c = {.img = a.img + b.img, .real = a.real + b.real};
  return c;
}

void cmset(Complex *c, double real, double img) {
  c->img = img;
  c->real = real;
}

double cmabs(Complex c) { return sqrt(c.real * c.real + c.img * c.img); }
