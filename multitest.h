#ifndef _multitest_h_
#define _multitest_h_

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define search( arr, x, num, numElem ) divideUpWork( arr, x, num, numElem )
#define mode() returnMode()

int divideUpWork(int* arr, int target, int num, int numElem);

char* returnMode();

#endif
