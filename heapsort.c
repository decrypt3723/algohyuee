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
	int last = readfile(argv[1], a); // last is heapsize - 1
	int* b;
	b = heapsort(a, &last);

	print_array(b, last);
}

int* heapsort(int* a, int* last) {
	int temp = *last;
	int b[temp + 1];
	build_heap(a, temp);
	int i = 0;
	while(i <= temp) {
		b[i] = extract_root(a, last);
		i++;
	}
	return b;
}

void build_Heap(int* a, int last) {
	for(int i = ( (last - 1) / 2); i > 0; i-- ) {
		max_heapify(a, i, last);
	}
}

int extract_root(int* a, int* last) {
	int temp;
	if(last != -1) {
		temp = a[0];
		a[0] = a[*last];
		max_heapify(a, 0, *last);
		*last--;
		return temp;
	}
	return NULL;
}

void max_heapify(int* a, int num, int last) {
	int largest = num;
	int left_child = find_left_child(num);
	int right_child = find_right_child(num);
	if( (left_child <= last) && (a[left_child] > a[largest]) ) {
		largest = left_child;
	}
	if( (right_child <= last) && (a[right_child] > a[largest]) ) {
		largest = right_child; 
	}
	if (largest != num) {
		max_heapify(a, largest, last);
	}
}

int find_left_child(int num) {
	return 2*num+1;
}
int find_right_child(int num) {
	return 2*num+2;
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

