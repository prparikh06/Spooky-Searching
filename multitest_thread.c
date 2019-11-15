#include "multitest.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int* mainArray;
int target;

struct thread_arg{
    int start;
    int end;
    int ind;
};

//Function to search
void* ThreadSearch(void* arg){
    struct thread_arg* ptr = (struct thread_arg*)arg;
    int start = ptr->start;
    int end = ptr->end;
    int i = 0;
    for(i = start; i<end; i++){
        if(mainArray[i] == target){
            pthread_exit(i);
        }
    }
    pthread_exit(251);
}
int divideUpWork(int* arr, int targ, int num){
    mainArray = arr;
    target = targ;
    int piece = 0; // # of nums in each section
    int numThreads = 0; // num of threads based on piece
    int threadCount = 0; // keeps count of number of threads
    // If array size is less than 250, we just divide it in 4 sections
    if(num < 250){
        piece = ceil(num / 4);
        numThreads = 4;
    }else{
        piece = 250;
        numThreads = ceil(num/250); //need to round up
    }
    printf("size of array: %d\n", num);
    //printf("piece: %d, numProcs: %d\n", piece, numProcs);

    pthread_t thread[numThreads];
    int i = 0;
    for(i = 0; i < numThreads; i++){
        struct thread_arg arg;
        arg.start = i;
        arg.end = i+piece;
        pthread_create(&thread[i], NULL, ThreadSearch, (void*)&arg);
        threadCount++;
    }

    int found = 251;
    for(i = 0; i < numThreads; i++){
        void* arg = NULL;
        pthread_join(thread[i], &arg);
        struct thread_arg* ptr = (struct thread_arg*)arg;
        if(ptr->ind != NULL){
            found = ptr->ind;
            found = (i*piece) + found;
        }
    }

    return found;



}
