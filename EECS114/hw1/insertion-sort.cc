/**
 *  \file insertion-sort.cc
 *
 *  \brief Implement your insertion sort in this file.
 *  Anderson Nguyen 68319094
 *  18205 EECS 114 HW1
 *
 *  This is an implementation of the binary insertion sort. Instead of the normal insertion sort, we are inserting the value directly into the correct position
 * without having to iterate through sequentially in the array.  
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "sort.hh"

int binarySearch(keytype* A, int value, int low, int high)
{
	/* if given array with duplicate low and high, this helps us determine the position of the value quickly.
	if the value is larger than the low element, we return position of low + 1 */
	if (high <= low) 
        	return (value > A[low])?  (low + 1): low; 
  
   	int mid = (low + high)/2; 
  	
	// returns position if value is found in the center
    	if(value == A[mid]) 
        	return mid+1; 
  
    	if(value > A[mid]) 
		// recursively calls binarySearch() and removes bottom half
        	return binarySearch(A, value, mid+1, high); 
	// recursively calls binarySearch() and removes upper half
    	return binarySearch(A, value, low, mid-1); 
}

void mySort(int N, keytype* A)
{
	int i, j, key, index;

	// allows us to iterate through array
	for (i = 1; i < N; ++i)	
	{
		key = A[i];
		j = i - 1;
		
		// finds position to insert value	
		index = binarySearch(A, key, 0, j);

		// shifts all elements in front of the insert by +1
		while (j >= index)
		{
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = key;
	} 
}

/* eof */
