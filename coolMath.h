#include <math.h>
#include <stdio.h>
#include <stdlib.h>



float standardDev(float times[], int l){

	float var = 0.0, mean, sum = 0.0, standDev = 0.0;
	int i;
	for (i = 0; i < l; i++) sum += times[i];
	mean = sum / (float) l; 
	for (i = 0; i < l; i++){
		var += pow((times[i] - mean) , 2);
	}
	
	var = var / (float) l; 
	standDev = (float) sqrt(var);
	return standDev;

}

float* minMax(float times[], int l){

	float min = times[0], max = times[0];
	
	int i;
	for (i = 0; i<l;i++){
		if (times[i] > max) max = times[i];
		if (times[i] < min) min = times[i];
	}
	float results[] = {min,max};	
	return results;
}
