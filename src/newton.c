#include<math.h>
/* implementazione del metodo di newton per risolvere equazioni non-lineari
 * come funziona:
 * date
 * - funzione f
 * - derivata f
 * - punto iniziale x_0
 * - tolleranza
 * - massimo numero di iterazioni
 * calcola lo zero della funzione.
*/


// calcola l'iterazione 
double newtonIt(double (*f)(double), double (*fd)(double), double x0){
	return x0 - f(x0)/fd(x0);
}
// wrapper
double newton(double (*f)(double), double (*fd)(double), double x0, double toll, unsigned int maxIteration){
	// inizializza errore
	double err = toll+1.0;
	// attuale iterazione
	unsigned int it = 0;
	// finche:
	// nit non e' maxiteration e il test d'arresto non da conclusione positiva
	double xk = x0;
	// calcola iterazione successiva
	while(err >= toll && it < maxIteration){
		// calcola nuova soluzione
		xk = newtonIt(f, fd, xk);
		// utilizzo test d'arresto del residuo per fermare metodo 
		err = fabs(f(xk))/fabs(f(x0)); 
		it++;
	}
	// restituisci la soluzione calcolata SE le iterazioni non sono le massime
	// devo capire come restituire un errore -> per ora restituisco INFINITY, ci sono molte altre opzioni migliori.
	if(it >= maxIteration){
		return INFINITY;
	}
	return xk;
}

