#include "multitest.h"
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <pthread.h> 




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
