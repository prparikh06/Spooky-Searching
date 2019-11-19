#include <stdlib.h>
#include <stdio.h>
#include "multitest.h"
#include <unistd.h>
#include <sys/time.h>


int MAX_ARR_SIZE = 12500;
int MAX_WORKERS = 50;


writeTimeToFile(FILE *fp){

	struct timeval startTime, endTime;


	int counter = 0;
	int i,ind,j;
	//create an array from size 1 to 375,000
	for (i = 1; i <=2000; i++){
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

		//given our array of size i, test using up to 50 threads/processes
		for (j = ceil((double) i / 250); j <= MAX_WORKERS && j <= i; j++){

			if (i % MAX_WORKERS != 0) continue;
			gettimeofday(&startTime,NULL);
			int x = search(array, randomTarget, i, j);
			gettimeofday(&endTime,NULL);
			float runTime = (float) endTime.tv_usec - startTime.tv_usec + endTime.tv_sec - startTime.tv_sec;
			char* status;
			if (x != -1) status = "found";
			else status = "not found";
			//write results to the file
			fprintf(fp, "%d\t%d\t%f\t%s\n", i,j,runTime,status);
			printf("arary size and thread num: %d and %d\n",i,j);
		}
		free(array);

	}
	fclose(fp);
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

	FILE *fp = fopen(argv[1],"w");
	writeTimeToFile(fp);



	/*
	int num = atoi(argv[1]);
	int numWorkers = -1;
	if (argv[2] != NULL) numWorkers = atoi(argv[2]);


    //FIRST GENERATION OF RANDOM LIST
    int* array = malloc(num * sizeof(int));
    int i;
    for(i = 0; i < num; i++){
        array[i] = i;
	//printf("%d ",array[i]);
    }

  //SCRAMBLE ARRAY

   for(i = 0; i < num; i++){
		int rand1 = rand() % num;
		int rand2 = rand() % num;
		int tmp1 = array[rand1];
		int tmp2 = array[rand2];
		array[rand2] = tmp1;
		array[rand1] = tmp2;
    }


    //SEARCH USING PROCESSES/THREADS
    int randomTarget = rand() % num;

	//START TIMING
	struct timeval startTime, endTime;
	float runTime = 0;

	gettimeofday(&startTime,NULL);
	int x;
	x = search(array, randomTarget, num, 5);
	gettimeofday(&endTime, NULL);
	runTime = (float) (endTime.tv_usec - startTime.tv_usec + endTime.tv_sec - startTime.tv_sec);



	/printf("Runtime %f\n", runTime);
   printf("searching: %d\nFound it at %d\n", randomTarget,x);
   ///////////////////////////
   int actual = check(array, randomTarget, num);
   printf("Actually at %d\n", actual);
	*/

    //EVERY TEST AFTERWARDS DOESN'T NEED TO GENERATE THE WHOLE LIST FROM SCRATCH, JUST SHUFFLE
	/*
 	int found = 5;
   array = shuffle(array, found);
   gettimeofday(&startTime,NULL);
	x = search(array, randomTarget, num, 10);
	gettimeofday(&endTime, NULL);
	*	free(array);
	*/
   return(0);



}
