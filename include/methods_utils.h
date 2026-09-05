#pragma once
#include<argp.h>

// codice riutilizzato, non specifico per metodo
struct vector {
  unsigned int dim;
  double *data;
};

struct vector generaTempi(double a, double b, double h);


// struttura che definisce gli argomenti per il programma.
// - a
// - b
// - h 
// sono tutti e tre dei valori double.
struct args {
	double a;
	double b;
	double h;
};
// parser per gli argomenti
error_t parser(int key, char *arg, struct argp_state *state);

// argomenti: strutturati nel seguente modo:
// char* name: 
// int key 
// char* arg   the name of an argument associated with this option
// int flags
// const char* doc
// int group
extern const struct argp_option options[];

/* Program documentation. */
extern const char doc[];
extern const struct argp arguments_structure;