#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int readfile(char* , int**);
void print_array(int*, int);
void swap(int* ,int, int); 
void heapsort(int** , int* , int**);
int extract_root(int* , int* );
void min_heapify(int* , int , int );
void build_heap(int* , int );
int find_left_child(int );
int find_right_child(int );

void heapsort(int** a, int* last, int** b) {
	int temp = *last;
	int i = 0;
	build_heap(*a, temp);
	*b = (int*) malloc(((*last)+1)*sizeof(int));
	while(i <= temp) {
		(*b)[i] = extract_root(*a, last);
		i++;
	}
}

void build_heap(int* a, int last) {
	for(int i = ( (last - 1) / 2); i >= 0; i-- ) {
		min_heapify(a, i, last);
	}
}

int extract_root(int* a, int* last) {
	int temp;
	if(*last >= 0) {
		temp = a[0];
		a[0] = a[*last];
		(*last)--;
		min_heapify(a, 0, *last);
		return temp;
	}
	return NULL;
}

void min_heapify(int* a, int num, int last) {
	int smallest = num;
	int left_child = find_left_child(num);
	int right_child = find_right_child(num);
	if( (left_child <= last) && (a[left_child] < a[smallest]) ) {
		smallest = left_child;
	}
	if( (right_child <= last) && (a[right_child] < a[smallest]) ) {
		smallest = right_child; 
	}
	if (smallest != num) {
		swap(a, smallest, num);
		min_heapify(a, smallest, last);
	}
}

int find_left_child(int num) {
	return (num*2)+1;
}
int find_right_child(int num) {
	return (num*2)+2;
}

void swap(int* a, int input1, int input2) {
	int temp;
	temp = a[input1];
	a[input1] = a[input2];
	a[input2] = temp;
}

int readfile(char* filename_input, int** arrayptr) {
	FILE* fptr;
	char filename[50];
	char stringbuf[50];
	int i = 0;
	strcpy(filename, filename_input);
	if((fptr = fopen(filename, "r")) == NULL) {
		printf("This file is not available.");
		exit(1);
	}
	// deciding size of array
	while((fscanf(fptr, "%s ", stringbuf)) != EOF) {
		i++;
	}
	
	// insert elements to memory-allocated array
	*arrayptr = (int*) malloc((i+1)*sizeof(int));
	rewind(fptr);
	
	i = 0;
	while((fscanf(fptr, "%s ", stringbuf)) != EOF) {
		(*arrayptr)[i++] = atoi(stringbuf);
	}
	fclose(fptr);
	return i-1;
}
void print_array(int* array, int last) {
	int i;
	for(int i = 0; i <= last; i++) {
		printf("%d ", array[i]);
		if((i+1) % 10 == 0) {
			printf("\n");
		}
	}
}

void write_file_array(char* output_name, int* array, int last) {
	FILE* fptw = fopen(output_name, "w");
	for(int i = 0; i <= last; i++) {
		fprintf(fptw, "%d ", array[i]);
	}
	fclose(fptw);
}

int main(int argc, char* argv[]) {
	clock_t start, end;
	int* a;
	int** aptr = &a;
	int* b;
	int** bptr = &b;
	int last = readfile(argv[1], aptr); // last is heapsize - 1
	int last_temp = last;
	start = clock();
	heapsort(aptr, &last, bptr);
	end = clock();
	printf("\n%.6lf ms for sorting.", (double)(end-start));
	// print_array(b, last_temp);
	write_file_array(argv[2], b, last_temp);
	free(a);
	free(b);
}