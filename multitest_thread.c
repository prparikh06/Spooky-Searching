#include "multitest.h"
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <pthread.h> 



void* FUNCTION_NAME(void* arg){

	//do stuff here
	printf("thead's ID: %d\n", (int*) arg);

}
int divideUpWork(int* arr, int target, int num){

    int piece = 0; // # of nums in each section
    int numThreads = 0; // num of threads based on piece
    int threadCounter = 0; // keeps count of number of thread
    // If array size is less than 250, we just divide it in 4 sections
    if(num < 250){
        piece = ceil(num / 4);
        numThreads = 4;
    }else{
        piece = 250;
        numThreads = ceil(num/250); //need to round up
    }
    printf("size of array: %d\n", num);
    printf("size of array: %d\n", num);
    printf("piece: %d, numProcs: %d\n", piece, numProcs);
    pthread_t pidThread[numThreads]; // retain's the children's pid
    int k = 0;

    //TIME TO CREATE THREADS AYYYY WHAT UP
    int i;
    for(i = 0; i < num; i = i + piece, k++){
        int start = i; //FLAG: forcurr thread to know where to start searching in arr
        printf("iteration i: %d\n", i);
        pthread_t = thread_ID:
        //TODO: since we need to use void* (void*) function, we need to format it as such and use a function for the actual search
        if((pidThread[k] = pthread_create(&thread_ID, NULL, FUNCTION_NAME, (void*) thread_ID) == -1){
            printf("oopsieeee there was an error\n");
        }
        
        //else do stuff

    }
}


void* testingThreads(void* arg){

	//do stuff here
	printf("thead's ID: %d\n", (int*) arg);

   
//	pthread_exit(NULL);
}

//test creating and closing a thread
int main(){
   
	int i = 0;
	
	pthread_t num1, num2;
	int status1 = pthread_create(&num1,NULL,testingThreads, (void*) num1);
    	int status2 = pthread_create(&num2,NULL,testingThreads, (void*) num2);
    	if (status1 != 0 || status2 != 0) printf("error"); 
	
	pthread_join(num1, NULL);
	pthread_join(num2, NULL);
	


pthread_exit(NULL);
printf("thread has been exited\n");

}
