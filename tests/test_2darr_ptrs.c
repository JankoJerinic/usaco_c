#include <stdlib.h>
#include <stdio.h>

struct Test {
	int i;
	char c;
	int p;
};

int main(void) {
	
	printf("sizeof(Struct { int; char }) = %zu.\n", sizeof(struct Test));

	//int (**arr2dptr)[3] = &arr2d;
	
	//int (*arr1dptr)[3] = arr2dptr[0];
	//int *arr = *arr1dptr;
	
	int arr[3] = { 13, 42, 134 };
	int (*arrptr)[3] = &arr;
	int *iptr = *arrptr;
		
	for (int i = 0; i < 3; ++i)  printf("%d\n", arr[i]);
	for (int i = 0; i < 3; ++i)  printf("%d\n", iptr[i]);

	int arr2d[][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	int (*arr2dptr)[][3] = &arr2d;

	printf("Casting pointer to array of array of 3 of int into a simple int* \n");
	iptr = (int *)arr2dptr; // You can hammer-cast a pointer to array of array of 3 of int into a simple int array
	for (int i = 0; i < 9; ++i)  printf("%d\n", iptr[i]);

	printf("Creating a pointer to int[3] \n");
	int (*arr1d)[3] = &arr2d[0];
	printf("%d\n", arr1d[0][1]);
	printf("%d\n", arr1d[1][1]);

	// Array to pointer decay.
	iptr = arr2d[0];
	printf("Printing using array to pointer decay, int[][] -> int[] -> int* \n");
	for (int i = 0; i < 9; ++i)  printf("%d\n", iptr[i]);
	
	printf("\n");
}
