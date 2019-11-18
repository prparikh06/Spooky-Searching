#include "multitest.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>

int divideUpWork(int* arr, int target, int num, int numElem){

    int piece = 0; // # of nums in each section
    int numProcs = 0; // num of child procs based on piece
    int numChild = 0; // keeps count of number of child

    // Testing phase param not -1
    if(numElem != -1){
        numProcs = numElem;
        piece = ceil((double)num/numElem);
	if (piece > 250) piece = 250;
    }
    // If array size is less than 250, we just divide it in 4 sections
    else if(num < 250){
        piece = ceil((double) num / 4);
        numProcs = 4;
    }else{
        piece = 250;
        numProcs = ceil((double)num/250); //need to round up
    }
    //printf("size of array: %d\n", num);
    //printf("piece: %d, numProcs: %d\n", piece, numProcs);
    pid_t pidChild[numProcs]; // retain's the children's pid
    int k = 0;

    //TIME TO FORK
    int i;
    for(i = 0; i < num; i = i + piece, k++){
        int start = i; //FLAG: for child to know where to start searching in arr
        //printf("iteration i: %d\n", i);
        //pid_t pid = fork();

        if((pidChild[k] = fork()) == -1){
            //printf("Error while fork the %d child : errno = '%s'.\n", k, strerror(errno));
        }else if(pidChild[k] == 0){
            //printf("I am child %d\n", getpid());
            //search for target
            int j;
            int ind = 0;
            if(start >= num) return 251;
            for(j = start; j < start+piece && j<num; j++){ //We could use a better search algo, I just used sequential for now
                if(arr[j] == target){
                    exit(ind);
                }
                ind++;
            }
            exit(251);
        }else{
            //printf("I am parent, my child is %d, I am %d\n", pidChild[k], getpid());
            numChild++;
        }

    }

     //printf("Waiting on all child.\n");
     int found = -1;
     //printf("numchild: %d, numProcs: %d\n", numChild, numProcs);
     pid_t stoppedChild;
     //Waits until all children are collected
     while(numChild >=0){
        int status = 0;

        stoppedChild = waitpid(-1, &status, 0);
        int i = 0;
        for (i = 0; i < numProcs; ++i) {
            if (stoppedChild == pidChild[i]) {
                //check if child returned without error
                if(WIFEXITED((status))){
                    int exit_status = WEXITSTATUS(status); //Get's return value
                    //printf("Child %d stopped.\n", i);
                    //printf("the status: %d\n", exit_status);
                    if(exit_status < 250 && exit_status >= 0){ //Child found the target
                        found = (i*piece) + exit_status;
                        //printf("the found: %d\n", found);
                    }

                }
            }
        }
        numChild--;
     }

    return found;
}
