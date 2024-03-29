#include "multitest.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int* mainArray;
int target;
int arraySize;
/*
    given array meta:
    meta[0] = start index of array
    meta[1] = end index of array
    meta[2] = index of target (if found)

*/

char* returnMode(){
    return "Multi-threading Mode";
}
//Function to search
void* ThreadSearch(void* arg){
    //printf("target: %d\n", target);

    int* ptr = (int*)arg;
    int start = ptr[0];
    int end = ptr[1];
    //printf("start: %d, end: %d\n", start, end);
    int i;
    for(i = start; i<end, i<arraySize ; i++){
        if(mainArray[i] == target){
            ptr[2] = i;
            //printf("true\n");

        }
    }

    //printf("ind is: %d\n", ptr[2]);
    int* ans = (int*) ptr[2];
    //free(arg);
    free(ptr);
    //pthread_exit(&arg);
    pthread_exit((void*) ans);
}
int divideUpWork(int* arr, int targ, int num, int numElem){

    mainArray = arr;
    target = targ;
    //printf("target: %d\n", target);
    int piece = 0; // # of nums in each section
    int numThreads = 0; // num of threads based on piece
    int threadCount = 0; // keeps count of number of threads
	arraySize = num;
    // Testing phase param not -1
    if(numElem != -1){
        numThreads = numElem;
	//printf("ceil(num/numElem) should be: %d\n", ceil(num/numElem));
        piece = ceil((double)num/numElem);

    }
    // If array size is less than 250, we just divide it in 4 sections
    else if(numElem == -1 && num < 250){
        piece = ceil((double)num / 4);
        numThreads = 4;
    }else{
        piece = 250;
        numThreads = ceil((double)num/250); //need to round up
    }

    //printf("size of array: %d\n", num);


    pthread_t thread[numThreads];
    int k = 0;
    int i;
    for(i = 0; i < num; i+= piece, k++){
        pthread_t handler;

        int* meta = (int*)malloc(sizeof(int)*3);
        meta[0] = i; meta[1] = i + piece; meta[2] = -1;
      //printf("arg start at: %d\n", meta[0]);
        int status = pthread_create(&handler, NULL, ThreadSearch, (void*)meta);

	if(status != 0){
            printf("error occurred while threading\n"); continue;
        }

        thread[k] = handler;
        //printf("handler: %d\n", handler);
        threadCount++;
    }
    //printf("numThreads: %d threadCount: %d\n", numThreads, threadCount);
    int found = -1;

    for(i = 0; i < numThreads; i++){
        int ans;

        pthread_join(thread[i], (void*)&ans);
        //printf("joined thread: %d\n", i);
        //printf("x is: %d\n", ans);

        if(ans != -1){
            found = ans;
            break;
        }

    }

    return found;


}
