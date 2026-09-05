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
int main(int argc, char** argv){

	struct args parsed_args= {1.0,2.0,0.1};


	// argp_parse (&argp, argc, argv, 0, 0, &arguments);
	argp_parse(&arguments_structure, argc, argv, 0, 0, &parsed_args);

	double a = parsed_args.a;
	double b = parsed_args.b;
	double h = parsed_args.h;

	if(a >= b){
		printf("a deve essere < di b.\n");
		return -1;
	}

	struct vector T = generaTempi(a,b,h);
	struct vector Y = euleroEsplicito(f, &T, 1.0, 1e-6, h);
	struct vector Y2 = euleroImplicito(f, fder, &T, 1.0, 1e-6, h);
	struct vector C = cnic(f, fder, &T, 1.0, 1e-6, h);
	struct vector H = heun(f,&T,1.0,h);
	
	
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
