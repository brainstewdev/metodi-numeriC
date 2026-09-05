#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "eulero.h"
#include "newton.h"
#include "cnic.h"
#include "methods_utils.h"
#include "heun.h"

double f(double t, double u) {
    return -4.0*u + (t*t)*sin(2.0*t);
}

double fder(double t, double u) {
    return -4.0;
}


// test function
int main(){
	struct vector T = generaTempi(0,1,0.1);
	struct vector Y = euleroEsplicito(f, &T, 1.0, 1e-6, 0.1);
	struct vector Y2 = euleroImplicito(f, fder, &T, 1.0, 1e-6, 0.1);
	struct vector C = cnic(f, fder, &T, 1.0, 1e-6, 0.1);
	struct vector H = heun(f,&T,1.0,0.1);
	
	
	// stampa una tabella per i dati
	printf("|t       \t|EE       \t|EI      \t|Heun    \t|CNIC    \t|\n");
	for (unsigned int i = 0; i < T.dim; i++){
		printf("|%.8f\t|%.8f\t|%.8f\t|%.8f\t|%.8f\t|\n", T.data[i], Y.data[i],Y2.data[i],C.data[i],H.data[i]);
	}

	free(T.data);
	free(Y.data);
	free(Y2.data);
	free(C.data);
}
