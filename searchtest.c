#include <stdlib.h>
#include <stdio.h>
#include "multitest.h"

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

    int num = 500;
    //FIRST GENERATION OF RANDOM LIST
    int* array = malloc(num * sizeof(int));
    int i = 0;
    for(i = 0; i < num; i++){
        array[i] = i;
    }
    for(i = 0; i < num; i++){
        printf("%d ", array[i]);
    }

    for(i = 0; i < num; i++){
        int randInd = rand() % num;
        int temp = array[randInd];
        array[randInd] = array[i];
        array[i] = temp;
    }
    printf("\n");
    for(i = 0; i < num; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
    //SEARCH USING PROCESSES/THREADS
    int x = search(array, 789, num);
    printf("Found it at %d\n", x);
    ////////////////////////////
    int actual = check(array, 789, num);
    printf("Actually at %d\n", actual);

    //EVERY TEST AFTERWARDS DOESN'T NEED TO GENERATE THE WHOLE LIST FROM SCRATCH, JUST SHUFFLE
    int found = 5;
    array = shuffle(array, found);
    printf("\n");
    for(i = 0; i < num; i++){
        printf("%d ", array[i]);
    }

    //OTHER TESTS



    return(0);



}
