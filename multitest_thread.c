#include "multitest.h"
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <libpthread.h> 

void* testingThreads(void* arg){

    printf("my name is priya!!!!\n");

}
//test creating and closing a thread
int main(){
    pthread_t num;
    int status = pthread_create(&num,NULL,testingThreads, NULL);
    if (status != 0) return 0; 
    printf("creating thread...num is %d\n",num);
    pthread_exit(num);
    printf("thread exited!\n");
}
