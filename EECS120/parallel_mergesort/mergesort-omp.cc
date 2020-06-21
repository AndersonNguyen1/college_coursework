// Anderson Nguyen
// 68319094

/**
 *  \file mergesort.cc
 *
 *  \brief Implement your mergesort in this file.
 *  \brief Implement my parallel mergesort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "sort.hh"
#define keytype_size sizeof(keytype) // this is the size of the type keytype

int size; // number of elements

void serialMerge(keytype *A, keytype *B, int left1, int left2, int left3, int right1, int right2);
void parallelMerge(keytype *A, keytype *B, int left1, int left2, int left3, int right1, int right2); 
void mergeSort(keytype *A, keytype *B, int l, int r);

int check (const void* first, const void* last) {
	keytype kfirst = *(const keytype *)first;
	keytype klast = *(const keytype *)last;

	if (kfirst < klast) // if the first is less than the last
		return -1;
	else if (kfirst == klast) // if equal
		return 0;
	else
		return 1;	
}

int binarySearch(keytype *A, keytype key, int l, int r) {
	int m;
	while (l < r) {
		m = (l + r) / 2; // find the middle value. avg
		if(key <= A[m])
			r = m; // the value of the middle is set to the right index
		else
		;	l = m + 1; // set the left value avg + 1 to accomodate
	}
	return r - 1;
}

void mergeSort(keytype *A, keytype *B, int l, int r) {
	int val = r - l + 1;
	if (val <= size) {
		qsort(A + l, val, keytype_size, check);
		return;
	}
	else {
		int m = l + ((r - l) / 2);

		#pragma omp task
		{
			mergeSort(A, B, l, m);
		}
		mergeSort(A, B, m + 1, r);

		#pragma omp taskwait
		//serialMerge(A, B, l, m + 1, l, m, r);
		parallelMerge(A, B, l, m + 1, l, m, r);
		memcpy(A + l, B + l, (r - l + 1)*keytype_size);
	}
}

void serialMerge(keytype *A, keytype *B, int left1, int left2, int left3, int right1, int right2) {
	while(left1 <= right1 && left2 <= right2) {
		if(A[left1] <= A[left2])
			B[left3++] = A[left1++];
		else
			B[left3++] = A[left2++];
	}

	while(left1 <= right1) {
		B[left3++] = A[left1++];
	}

	while(left2 <= right2) {
		B[left3++] = A[left2++];
	}
}

void parallelMerge(keytype *A, keytype *B, int left1, int left2, int left3, int right1, int right2) {
	int z = right1 - left1 + 1 + right2 - left2 + 1;

	if(z <= size)
		serialMerge(A, B, left1, left2, left3, right1, right2);
	else {
		int avg1 = (left1 + right1) / 2;
		int position = binarySearch(A, A[avg1], left2, right2);
		int avg2 = left3 + (avg1 - left1 + 1) + (position - left2 + 1);

		#pragma omp task
		{
			parallelMerge(A, B, left1, left2, left3, right1, right2);
		}

		parallelMerge(A, B, avg1 + 1, right1, position + 1, right2, avg2);

		#pragma omp taskwait
	}
}

void mySort (int N, keytype* A) {
	keytype *Z;
	Z = new keytype[N]; // this is a temp array used for holding the merged array values
	size = N;
	#pragma omp parallel
	{
		#pragma omp single nowait
		{
			mergeSort(A, Z, 0, N - 1);
		}
	}
}

/* eof */
