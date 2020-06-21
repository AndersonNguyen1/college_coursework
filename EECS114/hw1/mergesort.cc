/**
 *  \file mergesort.cc
 *
 *  \brief Implement your merge sort in this file.
 *
 *  This is an implementation of the merge sort algorithm. The way it works it that it recursively divides an array and stores it in a new temporary array.
 *  It keeps on dividing until each element of the given array is by itself. After they are all separated, they are merged back together and being sorted simulteously.
 *
 *  Anderson Nguyen 68319094
 *  18205 EECS 114 HW1 3B
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "sort.hh"

void merge(keytype* A, int left, int mid, int right)
{
	int a, b, c;
	// left side indices
	int leftElements = mid - left + 1;
	//right side indices
	int rightElements = right - mid;
	
	int L[leftElements], R[rightElements];

	// fills in array with values
    	for (a = 0; a < leftElements; a++) 
        	L[a] = A[left + a]; 
    	for (b = 0; b < rightElements; b++) 
        	R[b] = A[mid + 1 + b];

	a = 0;
	b = 0;
	c = left;

	// determines which array has the smaller value and then substitutes it into the main array until all elements are sorted 
	while (a < leftElements && b < rightElements)
	{
		if (L[a] <= R[b])
		{
			A[c] = L[a];
			a++;
		}
		else
		{
			A[c] = R[b];
			b++;
		}
		c++;
	} 

	// copies any remaining elements of L[] when there are no more R[] elements to compare it to
	while (a < leftElements) 
    	{ 
        	A[c] = L[a]; 
        	a++; 
        	c++; 
	} 

	// copies any remaining elements of R[] when there are no more L[] elements to compare it to
    	while (b < rightElements) 
    	{ 
        	A[c] = R[b]; 
        	b++; 
        	c++;
	} 
}

void mergeSort(keytype* A, int low, int high)
{
	if (low < high)
	{
		int mid = low + (high - low)/2;

		// recursively calls itself until array is fully divided into individual elements		
		mergeSort(A, low, mid);
		mergeSort(A, mid + 1, high);

		// combines all of the elements back together
		merge(A, low, mid, high);	
	}
}

void mySort (int N, keytype* A)
{
	int low = 0;
	int high = N - 1;

	mergeSort(A, low, high);
}

/* eof */
