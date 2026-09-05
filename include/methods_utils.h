#pragma once
// codice riutilizzato, non specifico per metodo
struct vector {
  unsigned int dim;
  double *data;
};

struct vector generaTempi(double a, double b, double h);