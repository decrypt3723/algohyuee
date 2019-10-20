#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int readfile(char* , int*);
void mergesort(int*, int, int);
void merge(int*, int, int ,int);
void print_array(int*, int);

int main (int argc, char* argv[]) {
	int a[1000];
	int first = 0;
	int last;
	last = readfile(argv[1], a);
	mergesort(a,first,last);
	print_array(a,last);
}

void mergesort(int* a, int q, int r) {
	int middle = ((q+r) / 2);
	if (q < r) {
		printf("%d\n",middle);
		mergesort(a, q, middle);
		mergesort(a, middle+1, r);
		merge(a,q,r,middle);
	}
}

void merge(int* a, int q, int r, int middle) {
	int i = q;
	int j = middle+1;
	int k = 0;
	int b[r-q+1];
	printf("~~\n");
	while( k < (r-q+1)) {
		if(i == (middle+1)) {
			printf("1\n");
			b[k] = a[j];
			j++;
		}
		else if (j == (r+1)) {
			printf("2\n");
			b[k] = a[i];
			i++;
		}
		else if (a[i] <= a[j]) {
			printf("3\n");
			b[k] = a[i];
			i++;
		}
		else {
			printf("4\n");
			b[k] = a[j];
			j++;
		}
		k++;

	}
	
	i = q;
	for (k = 0; k < r-q+1; k++) {
		a[i] = b[k];
		i++;
	}
}
int readfile(char* filename_input, int* array) {
	FILE* fptr;
	char filename[50];
	char stringbuf[50];
	int intbuf;
	int i = 0;
	printf("5\n");
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
	printf("6\n");
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
