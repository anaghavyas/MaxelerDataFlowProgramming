#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include <MaxSLiCInterface.h>

#define DATA_SIZE 256
//#define SWAP(a,b) {int temp; temp = a; a = b; b = temp;}

double data[DATA_SIZE];

void siftDown( double *a, int k, int N);

void swap(double *m, double *n)
{
	double tmp;
	tmp = *m;
	*m = *n;
	*n = tmp;
}

void heap_sort( double *a, int N){
	/* heapify */
	for (int k = N/2; k >= 0; k--) {
		siftDown( a, k, N);
	}

	while (N-1 > 0) {
		/* swap the root(maximum value) of the heap
		with the last element of the heap */
		double *x = &a[N-1];
		double *y = &a[0];
		swap(x, y);

		/* put the heap back in max-heap order */

		siftDown(a, 0, N-1);
		/* N-- : decrease the size of the heap by one
		so that the previous max value will
        	stay in its proper placement */
		N--;
	}
}

void siftDown( double *a, int k, int N){
	while ( k*2 + 1 < N ) {
		/* For zero-based arrays, the children are 2*i+1 and 2*i+2 */
		int child = 2*k + 1;

		/* get bigger child if there are two children */
		if ((child + 1 < N) && (a[child] < a[child+1])) child++;

		if (a[k] < a[child]) {   /* out of max-heap order */
			double *x = &a[child];
			double *y = &a[k];
			swap(x,y);
			//swap( a[child], a[k] );
			/* repeat to continue sifting down the child now */
			k = child;
		}
		else
			return;
	}
}

void heap_sort_dfe( double *inAddressA, int N){
	/* heapify */
	for (int k = N/2; k >= 0; k--) {
		siftDown( a, k, N);
	}

	while (N-1 > 0) {
		/* swap the root(maximum value) of the heap
		with the last element of the heap */
		double *outDataB;
		double *outDataA;
		//swap(x, y);
		HeapSortMaxeler(
					size,
					&inAddressA[N-1],	&inAddressA[0],
					outDataA, outDataB,
					romContents);

		/* put the heap back in max-heap order */

		siftDown(a, 0, N-1);
		/* N-- : decrease the size of the heap by one
		so that the previous max value will
        	stay in its proper placement */
		N--;
	}
}




int main()
{
	const int size = DATA_SIZE;
	int sizeBytesFloat = size * sizeof(float);
	int sizeBytesDouble = size * sizeof(double);
	int sizeBytesInt = size * sizeof(uint8_t);

	uint8_t *inAddressA = malloc(sizeBytesInt);
	uint8_t *inAddressB = malloc(sizeBytesInt);

	double *romContents = malloc(sizeBytesDouble);
	double *romContentsOrdered = malloc(sizeBytesDouble);

	float *outDataA = malloc(sizeBytesFloat);
	float *outDataB = malloc(sizeBytesFloat);

	// TODO Generate input data
	for(int i = 0; i < size; ++i) {
		romContents[i] = rand() % 100;
		romContentsOrdered[i] = 0;
		printf("%d ", (int)romContents[i]);
	}
	printf("\n");


	//loadData in Data Array
	for (int i = 0; i < size; i++) {
		data[i] = romContents[i];
		inAddressA[i] = romContents[i];
	}
	//HeapSort using C
	clock_t start = clock();
	heap_sort(data, size);
	clock_t end = clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;

	printf("Execution Time for %i elements using HeapSort with C implementation: %4.5f seconds\n",DATA_SIZE,seconds);
	for(int i = 0; i < size; ++i) {
		printf("%d ", (int)data[i]);
	}
	printf("\n");


	printf("Running DFE.\n");
	start = clock();
	heap_sort_dfe(inAddressA, size, inAddressB); //Heap Sort using the DFE engine

	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Execution Time for %i elements using HeapSort using DFE Kernel implementation: %4.5f seconds\n",DATA_SIZE,seconds);

	return 0;
}
