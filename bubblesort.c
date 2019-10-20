#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int*, int, int);
int readfile(char*, int*);

int main(int argc, char* argv[]) {
	int a[1000];
	int array_length;
	int first, last;
	int i;

	last = readfile(argv[1], a);
	i = 0;
	for(int i = last; i > 0; i--) {
		for(int j = 0; j < i; j++) {
			if(a[j] > a[j+1]) {
				swap(a,j,j+1);
			}
		}
	}
	for(int i = first; i <= last; i++) {
		printf("%d ", a[i]);
		if((i % 10) == 0) {
			printf("\n");
		}
	}
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
