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
    int target;
};

//Function to search
void* ThreadSearch(void* arg){
    printf("target: %d\n", target);
    //struct thread_arg* ptr = (struct thread_arg*)arg;
    int* ptr = (int*)arg;
    int start = ptr[0];
    int end = ptr[1];
    printf("start: %d, end: %d\n", start, end);
    int f = 0;
    int i = 0;
    for(i = start; i<end; i++){
        if(mainArray[i] == target){
            ptr[2] = i;
            printf("true\n");
            f = 1;
        }
    }
    //if(f == 0){
     //   ptr->ind = 251;
    //}
    printf("ind is: %d\n", ptr[2]);
    pthread_exit(&arg);
}
int divideUpWork(int* arr, int targ, int num){
    mainArray = arr;
    target = targ;
    printf("target: %d\n", target);
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
    printf("numThreads: %d threadCount: %d\n", numThreads, threadCount);

    pthread_t thread[numThreads];
    int k = 0;
    int i = 0;
    for(i = 0; i < num; i+= piece, k++){
        pthread_t handler;

        struct thread_arg* arg = malloc(sizeof(struct thread_arg));
        arg->start = i;
        arg->end = i+piece;
        arg->target = targ;
        int* meta = (int*)malloc(sizeof(int)*3);
        meta[0] = i; meta[1] = i + piece; meta[2] = -1;
        printf("arg start at: %d\n", arg->start);
        int status = pthread_create(&handler, NULL, ThreadSearch, (void*)meta);
        if(status != 0){
            printf("error occurred while threading\n");
        }
        thread[k] = handler;
        printf("handler: %d\n", handler);
        threadCount++;
    }
    printf("numThreads: %d threadCount: %d\n", numThreads, threadCount);
    int found = 251;
    for(i = 0; i < numThreads; i++){
        struct thread_arg* ptr;
        pthread_join(thread[i], (void*)&ptr);
        printf("joined thread: %d\n", i);
        //struct thread_arg* ptr = (struct thread_arg*)arg;
        int x = ptr->ind;
        printf("x is: %d\n", x);
        if(ptr->ind != 251){
            found = ptr->ind;
            found = (i*piece) + found;
        }
    }
    pthread_exit(NULL);
    return found;



}
