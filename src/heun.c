#include "heun.h"
#include<stdlib.h>

struct vector heun(double (*f)(double t, double u), const struct vector * T, double y0, double h){
    // creo vettore di destinazione
	struct vector dest = {T->dim, malloc(T->dim*sizeof(double))};
	// controllo che l'array destinazione abbia il giusto numero di elementi
	if(dest.dim != T->dim){
		free(dest.data);
		dest.dim = -1;
		return dest;
	}
	// ottengo la dimensione dell'array dei tempi
	size_t n = dest.dim;
	double uk_p = y0; // soluzione all'intervallo precedente
	// imposto il valore associato alla y0
	dest.data[0] = y0;
    // variabile che rappresenta la un* all'iterazione n
    double ustar = 0.0;
	// calcolo le T
	for(size_t i = 1; i<n; i++){
		// utilizza formula per calcolare l'elemento corrente utilizzando il precedente.
		// dest.data[i] = uk_p + h*(f(T->data[i-1],uk_p));
        ustar = uk_p + h*(f(T->data[i-1],uk_p));
        dest.data[i] = uk_p + h/2 * (f(T->data[i-1],uk_p) + f(T->data[i],ustar));
		// imposto uk_p al vlaore calcolato in questa iterazione (precedente nel ciclo successivo)
		uk_p = dest.data[i];
	}
	return dest;
}