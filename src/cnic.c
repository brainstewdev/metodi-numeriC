#include "cnic.h"
#include<stdlib.h>
#include "newton.h"

struct vector cnic(double (*f)(double t, double u), double (*fder)(double t, double y),  const struct vector * T, double y0, double toll, double h){
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
	// Calcola le Y...
	for(size_t i = 1; i<n; i++){
        // come per eulero implicito ma utilizzo le formule di crank nicolson.
		double fs(double u) { return -u+uk_p+(h/2)*(f(T->data[i-1], uk_p) + f(T->data[i], u)); };
		double fsder(double u) { return  (h/2)*fder(T->data[i], u)-1; };

		// calcolo dunque la soluzione tramite metodo di newton e imposto il dato nella 
		// struttura associato al tempo corrente.
		dest.data[i] = newton(fs,fsder, uk_p, 1e-6, 200);
		// aggiorno uk_p per essere associato alla u appena calcolata (che nella prossima
		// iterazione sara' quella passata)
		uk_p = dest.data[i];
	}
	// restituisco la struttura
	return dest;
}