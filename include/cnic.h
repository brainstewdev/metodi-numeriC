#pragma once
#include "methods_utils.h"

struct vector cnic(double (*f)(double t, double u), double (*fder)(double t, double y),  const struct vector * T, double y0, double toll, double h);