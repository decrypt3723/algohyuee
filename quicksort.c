#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int readfile(char* , int*);
void print_array(int*, int);
void swap(int* ,int, int); 
void quicksort(int*, int, int);
int partition(int*, int, int);

int main(int argc, char* argv[]) {
	srand((unsigned)time(NULL));
	int a[1000];
	int first = 0;
	int last = readfile(argv[1],a);
	quicksort(a, first, last);

	print_array(a, last);
}

void quicksort(int* array, int first, int last) {
	printf("1\n");
	if(last > first) {
		int pivot = partition(array, first, last);
		quicksort(array, first, pivot-1);
		quicksort(array, pivot+1, last);
	}	
}

int partition(int* array, int first, int last) {
	int pivot = rand() % (last - first + 1);
	int key = array[pivot + first];
	int j = first;
	swap(array, last, pivot + first);
	printf("%d ", pivot);
	for(int i = first; i < last; i++) {
		if(key > array[i]) {
			swap(array,i,j);
			j++;
		}
	}
	swap(array, last, j);
	return j;
}

void swap(int* a, int input1, int input2) {
	int temp;
	temp = a[input1];
	a[input1] = a[input2];
	a[input2] = temp;
}

int readfile(char* filename_input, int* array) {
	FILE* fptr;
	char filename[50];
	char stringbuf[50];
	int intbuf;
	int i = 0;
	strcpy(filename, filename_input);
	if((fptr = fopen(filename, "r")) == NULL) {
		printf("This file is not available.");
		exit(1);
	}
	while((fscanf(fptr, "%s ", stringbuf)) != EOF) {
		intbuf = atoi(stringbuf);
		array[i++] = intbuf;
	}
	fclose(fptr);
	return i-1;
}
void print_array(int* array, int last) {
	int i;
	for(int i = 0; i <= last; i++) {
		printf("%d ", array[i]);
		if(i % 10 == 0) {
			printf("\n");
		}
	}
}
