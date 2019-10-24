#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int readfile(char* , int*);
void print_array(int*, int);
void swap(int* ,int, int); 

int main(int argc, char* argv[]) {
	int a[1000];
	int last = print_array(argv[1], a); // last is heapsize - 1
	heapsort(a, last);
}

int heapsort(int* a, int last) {
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

