#include<stdlib.h>
#include "methods_utils.h"

struct vector generaTempi(double a, double b, double h){
	struct vector tempi = {((b-a)/h)+1, (double*)malloc(((b-a)/h+1)*sizeof(double))};

	for (unsigned int i = 0; i < tempi.dim; i++){
		tempi.data[i] = a + h*i;
	}
	return tempi;
}