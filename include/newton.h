#pragma once
// definizioni per il metodo di newton.
double newton(double (*f)(double), double (*fd)(double), double x0, double toll, unsigned int maxIteration);
