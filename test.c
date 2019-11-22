#include <stdio.h>
#include <stdlib.h>
#include "coolMath.h"


int main(){

	float array[] = {0.0, 1.0, 9.0};
	int len =3;
	float hansonKySux = standardDev(array,len);
	printf("%f\n", hansonKySux);
	float *results;
	results = minMax(array,len);
	printf("min: %f, max: %f\n",results[0], results[1]); 

}
