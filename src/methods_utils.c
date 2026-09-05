#include<stdlib.h>
#include "methods_utils.h"

struct vector generaTempi(double a, double b, double h){
	struct vector tempi = {((b-a)/h)+1, (double*)malloc(((b-a)/h+1)*sizeof(double))};

	for (unsigned int i = 0; i < tempi.dim; i++){
		tempi.data[i] = a + h*i;
	}
	return tempi;
}

const struct argp_option options[] = {
	{"estremosx",'a', "DOUBLE",0, "estremo sinistro dell'intervallo di definizione del problema di Cauchy.", 0},
	{"estremodx",'b', "DOUBLE",0, "estremo destro dell'intervallo di definizione del problema di Cauchy.", 0},
	{"passo",'h', "DOUBLE",0, "passo per il problema.", 0},
	{0}
};

const char doc[] =
  "Programma di test per risolvere problemi di cauchy con metodi numerici.";

const struct argp arguments_structure = {options,parser, 0, 0, 0,0,doc};

error_t parser(int key, char *arg, struct argp_state *state){
	struct args* arguments = state->input;

	switch (key)
	{
	case 'a':
		// Si tratta di a. 
		arguments->a = atof(arg);
		break;	
	case 'b':
		// Si tratta di b. 
		arguments->b = atof(arg);
		break;	
	case 'h':
		// Si tratta di h. 
		arguments->h = atof(arg);
		break;
	default:
		break;
	}
	return 0;
}
