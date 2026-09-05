struct vector {
  unsigned int dim;
  double *data;
};

struct vector euleroImplicito(double (*f)(double t, double u), double (*fder)(double t, double y), const struct vector * T, double y0, double toll, double h);

struct vector euleroEsplicito(double (*f)(double t, double u), const struct vector * T, double y0, double toll, double h);
