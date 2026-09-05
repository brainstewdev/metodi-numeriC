#include<stdlib.h>
#include "eulero.h"
#include "newton.h"

///// ATTENZIONE: 	Per scrivere queste funzioni ho utilizzato nested function, che non sono disponibili in c standard!!!
/////				Per compilare utilizzate GCC!
/////				E' possibile NON utilizzare nested function reimplementando il metodo di netwon internamente a euleroImplicito.
/////				TODO: implementare questa versione per compilatori che non siano GCC con ifdef.

/*
 * implementazione dei metodi di eulero implicito ed esplicito per l'approssimazione
 * della soluzione di ODE.
 * Voglio rendere le implementazioni simili a quelle di matlab: dato un intervallo di tempi
 * voglio che mi venga restituita una struttura contente l'approsimazione della funzione soluzione
 * valutata nei tempi.
 */

/*
	Per resituire l'approssimazione calcolata utilizzo una struttura semplice. 
	Tale struttura e' descritta nell'header dove dichiaro questi metodi seguenti.
	Questa struttura contiene due elementi:
	- un elemento rappresentante quanti elementi sono presenti nella struttura
	- un elemento data, che non e' altro che un puntatore ai dati.
	Questo e' fatto per rendere semplice ottenere le dimensioni del vettore senza utilizzare metodi piu' astrusi
*/
struct vector euleroImplicito(double (*f)(double t, double u), double (*fder)(double t, double y),  const struct vector * T, double y0, double toll, double h){
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
		// in questo caso devo utilizzare il metodo di eulero implicito.
		// calcola gli zeri della funzione tramite newton 
		// -- QUA INIZIA PARTE NON SUPPORTATA DA C STANDARD! --- //
		// calcolo le funzioni specializzate fs(x) e fs'(x), fissando t per f e f'
		// essenzialmente sto utilizzando una closure, creando delle funzioni specializzate
		// partendo da funzioni generiche. Niente di incredibile ma il fatto che non siano 
		// supportate da C le nested function rende il tutto basato sulla grazia di GCC.
		// In modo molto chiaro: queste funzioni sono ESATTAMENTE come calcolare
		// f(t_{n+1},u_{n+1}). Soltanto che dato che il metodo di newton, per come l'ho 
		// implementato richiede una funzione che lavori su una sola variabile
		// vado a fissare il parametro t_{n+1} (che e' fissato per l'iterazione del ciclo...)
		// in modo tale da creare una funzione generica che mi calcoli la f(u_{n+1}) sempre 
		// in t_{n+1}. All'iterazione seguente questa funzione verra' dunque ricreata andando
		// a sostituire il parametro t_{n+1} con quello aggiornato. 
		double fs(double u) { return -u+uk_p+ h*(f(T->data[i], u)); };
		double fsder(double u) { return  h*(fder(T->data[i], u))-1; };

		// calcolo dunque la soluzione tramite metodo di newton e imposto il dato nella 
		// struttura associato al tempo corrente.
		dest.data[i] = newton(fs,fsder, uk_p, 1e-6, 200);
		// --- FINE PARTE NON SUPPORTATA DA C STANDARD --- //

		// aggiorno uk_p per essere associato alla u appena calcolata (che nella prossima
		// iterazione sara' quella passata)
		uk_p = dest.data[i];
	}
	// restituisco la struttura
	return dest;
}
// Questo e' il caso banale, niente di speciale.
struct vector euleroEsplicito(double (*f)(double t, double u), const struct vector * T, double y0, double toll, double h){
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
	// calcolo le T
	for(size_t i = 1; i<n; i++){
		// utilizza formula per calcolare l'elemento corrente utilizzando il precedente.
		dest.data[i] = uk_p + h*(f(T->data[i-1],uk_p));
		// imposto uk_p al vlaore calcolato in questa iterazione (precedente nel ciclo successivo)
		uk_p = dest.data[i];
	}
	return dest;
}
