#include "complex.h"

Complex cmadd(Complex a, Complex b) {
  // just add respective real and imaginary parts of the two numbers
  Complex c = {.img = a.img + b.img, .real = a.real + b.real};
  return c;
}

// helper function to set help assign a reference
// to a complex val
void cmset(Complex *c, double real, double img) {
  c->img = img;
  c->real = real;
}

// get the absolute val (often called z), it's just the pythagorean theorem
double cmabs(Complex c) { return sqrt(c.real * c.real + c.img * c.img); }
