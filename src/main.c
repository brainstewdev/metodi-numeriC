#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "eulero.h"
#include "newton.h"

double f(double t, double u) {
    return -4.0*u + (t*t)*sin(2.0*t);
}

double fder(double t, double u) {
    return -4.0;
}

struct vector generaTempi(double a, double b, double h){
	struct vector tempi = {((b-a)/h)+1, malloc(((b-a)/h+1)*sizeof(double))};

	for (unsigned int i = 0; i < tempi.dim; i++){
		tempi.data[i] = a + h*i;
	}
	return tempi;
}

// test function
int main(){
	struct vector T = generaTempi(0,5,0.01);
	struct vector Y = euleroEsplicito(f, &T, 1.0, 1e-6, 0.1);
	struct vector Y2 = euleroImplicito(f, fder, &T, 1.0, 1e-6, 0.1);
	
	// stampa una tabella per i dati
	printf("|t       \t|EE       \t|EI      \t|\n");
	for (unsigned int i = 0; i < T.dim; i++){
		printf("|%.8f\t|%.8f\t|%.8f\t|\n", T.data[i], Y.data[i],Y2.data[i]);
	}

	free(T.data);
	free(Y.data);
	free(Y2.data);
}
