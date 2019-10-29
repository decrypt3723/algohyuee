#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define dataType char
#define dataTypeFormat "%c "

void heapsort(dataType** a, int* last, dataType** b) {
	int temp = *last;
	int i = 0;
	build_heap(*a, temp);
	*b = (dataType*) malloc(((*last)+1)*sizeof(dataType));
	while(i <= temp) {
		(*b)[i] = extract_root(*a, last);
		i++;
	}
}

void build_heap(dataType* a, int last) {
	for(int i = ( (last - 1) / 2); i >= 0; i-- ) {
		min_heapify(a, i, last);
	}
}

int extract_root(dataType* a, int* last) {
	int temp;
	if(*last >= 0) {
		temp = a[0];
		a[0] = a[*last];
		(*last)--;
		min_heapify(a, 0, *last);
		return temp;
	}
	return 0;
}

void min_heapify(dataType* a, int num, int last) {
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

void swap(dataType* a, int input1, int input2) {
	int temp;
	temp = a[input1];
	a[input1] = a[input2];
	a[input2] = temp;
}

int readfile(char* filename_input, dataType** arrayptr) {
	FILE* fptr;
	char filename[50];
	char stringbuf[50];
	int i = 0;
	dataType buf;
	strcpy(filename, filename_input);
	if((fptr = fopen(filename, "r")) == NULL) {
		printf("This file is not available.");
		exit(1);
	}
	// deciding size of array
	while((fscanf(fptr, dataTypeFormat, stringbuf)) != EOF) {
		i++;
	}
	
	// insert elements to memory-allocated array
	*arrayptr = (dataType*) malloc((i+1)*sizeof(dataType));
	rewind(fptr);
	
	i = 0;
	while((fscanf(fptr, dataTypeFormat, &buf)) != EOF) {
		(*arrayptr)[i++] = buf;
	}
	fclose(fptr);
	return i-1;
}
void print_array(dataType* array, int last) {
	int i;
	for(int i = 0; i <= last; i++) {
		printf(dataTypeFormat, array[i]);
		if((i+1) % 10 == 0) {
			printf("\n");
		}
	}
}

void write_file_array(char* output_name, dataType* array, int last) {
	FILE* fptw = fopen(output_name, "w");
	for(int i = 0; i <= last; i++) {
		fprintf(fptw, dataTypeFormat, array[i]);
	}
	fclose(fptw);
}

int main(int argc, char* argv[]) {
	clock_t start, end;
	dataType* a;
	dataType** aptr = &a;
	dataType* b;
	dataType** bptr = &b;
	int last = readfile(argv[1], aptr); // last is heapsize - 1
	int last_temp = last;
	print_array(a,last);
	start = clock();
	heapsort(aptr, &last, bptr);
	end = clock();
	printf("\n%.6lf ms for sorting.", (double)(end-start));
	// print_array(b, last_temp);
	write_file_array(argv[2], b, last_temp);
	free(a);
	free(b);
}
