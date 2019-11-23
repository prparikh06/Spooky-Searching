#include <stdlib.h>
#include <stdio.h>
#include "multitest.h"
#include <unistd.h>
#include <sys/time.h>
#include <math.h>



int MAX_WORKERS = 50;

float mean(float times[], int l){
    float sum, theMean = 0.0;
    int i;
    for (i = 0; i < l; i++) sum += times[i];
	theMean = sum / (float) l;
	return theMean;
}

float standardDev(float times[], int l, float mean){

	float var = 0.0, sum = 0.0, standDev = 0.0;
	int i;
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



writeTimeToFile(int min, int max){
    char* currentMode = mode();
    printf("%s\n", currentMode);
	int MAX_ARR_SIZE = max;
	struct timeval startTime, endTime;
	//FILE *fp = fopen(filename,"w");

	int counter = 0;
	int i,ind,j;
	//create an array of diff sizes
	for (i = min; i <=MAX_ARR_SIZE; i+=100){
		int* array = malloc(i * sizeof(int));
		//make the array
		for(ind = 0; ind < i; ind++)
	        	array[ind] = ind;
    		//shuffle the array
   		for(ind = 0; ind < i; ind++){
			int rand1 = rand() % i;
			int rand2 = rand() % i;
			int tmp1 = array[rand1];
			int tmp2 = array[rand2];
			array[rand2] = tmp1;
			array[rand1] = tmp2;
		}

		//random target:
		int randomTarget = rand() % i;
		int numofWorkers = 0;
        if(i < 250){
            if(MAX_WORKERS < i){
                numofWorkers = MAX_WORKERS - (int)(ceil((double) i / 250)) + 1;
            }else{
                numofWorkers = i - (int)(ceil((double) i / 250)) + 1;
            }

        }else{
            numofWorkers = MAX_WORKERS - (int)(ceil((double) i / 250)) + 1;
        }

		float* times = malloc(sizeof(int) * numofWorkers);
		int k = 0;
        printf("Testing array size %d, Target:%d\n", i, randomTarget);
		//given our array of size i, test using up to 50 threads/processes
		for (j = ceil((double) i / 250); j <= MAX_WORKERS && j <= i; j++, k++){

			//if (i % MAX_WORKERS != 0) continue;
			gettimeofday(&startTime,NULL);
			int x = search(array, randomTarget, i, j);
			gettimeofday(&endTime,NULL);
			float runTime = (float) endTime.tv_usec - startTime.tv_usec + 1000000*(endTime.tv_sec - startTime.tv_sec);
			times[k] = runTime;
			//fprintf(fp,"%d\t%d\t%f\n", i,j,runTime);
			printf("Arr Size: %d\tNum of Workers: %d\tRuntime: %f\tIndex found: %d\n", i,j,runTime, x);
			//char* status;
			//if (x != -1) status = "found";
			//else status = "not found";
			//write results to the file



			//printf("arary size and thread num: %d and %d\n",i,j);
		}
		float theMean = mean(times,k);
		float stdDiv = standardDev(times,k,theMean);
		float *results = minMax(times,k);;
        //printf("numofWorkers: %d, times size: %d\n", numofWorkers, k);
        printf("mean: %f, std: %f, min: %f, max: %f\n", theMean, stdDiv, results[0], results[1]);
        free(times);
		free(array);

	}
	//fclose(fp);
}




int* shuffle(int* arr, int i){
    size_t num = sizeof(arr)/sizeof(arr[0]);
    int randInd = rand() % num;
    int temp = arr[randInd];
    arr[randInd] = arr[i];
    arr[i] = temp;

    return arr;

}

int check(int* arr, int target, int size){
    int i = 0;
    for(i = 0; i<size; i++){
        if(arr[i] == target){
        return i;
        }
    }
    return -1;

}
int main(int argc, char* argv[]){
    int min = 100;
    int max = 12500;
    int workers = 50;
    printf("Testing array sizes ranging from %d to %d, with max number of workers as %d\n", min, max, workers);
	//FILE *fp = fopen(argv[1],"w");
	writeTimeToFile(min, max);


   return(0);



}
