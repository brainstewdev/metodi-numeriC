#pragma once
#include "methods_utils.h"

// dichiarazione metodi relativi al metodo di Heun.
struct vector heun(double (*f)(double t, double u), const struct vector * T, double y0, double h);
