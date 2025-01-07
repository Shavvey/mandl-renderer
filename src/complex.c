#include "complex.h"

// helper function to add two complex numbers
Complex cmadd(Complex a, Complex b) {
  // just add respective real and imaginary parts of the two numbers
  Complex c = {.img = a.img + b.img, .real = a.real + b.real};
  return c;
}

// get the absolute val (often called z), it's just the pythagorean theorem
double cmabs(Complex c) { return sqrt((c.real * c.real) + (c.img * c.img)); }

// compute the square of the complex number
Complex cmsqr(Complex c) {
  // (a + bi)^2 = a^2 + 2abi - b^2 = a^2 - b^2 + 2abi
  Complex cmsqr = {.real = (c.real * c.real) + (c.img * c.img * -1),
                   .img = (2 * c.img * c.real)};
  return cmsqr;
}
