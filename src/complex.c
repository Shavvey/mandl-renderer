#include "complex.h"

Complex cadd(Complex a, Complex b) {
  Complex c = {.img = a.img + b.img, .real = a.real + b.real};
  return c;
}

void cset(Complex *c, double real, double img) {
  c->img = img;
  c->real = real;
}
