#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


void swap(int* a, int input1, int input2) {
	int temp;
	temp = a[input1];
	a[input1] = a[input2];
	a[input2] = temp;
}

// median of three implemented
//
int partition(int* array, int first, int last) {
	int median = first + (last-first)/2;
	int i, key, j;
	int* temp = (int*)malloc(sizeof(int)*3);
	
	temp[0] = array[first];
	temp[1] = array[median];
	temp[2] = array[last];

	//bubble sort of 3 elements
	for(i = 2; i > 0; i--) {
		for(j = 0; j < i; j++) {
			if(temp[j] > temp[j+1]) {
			swap(temp, j, j+1);
			}
		}
	}
	array[first] = temp[0];
	array[median] = temp[2];
	array[last] = temp[1];
	free(temp);	
	
	key = array[last];
	j = first;
	
	for(i = first; i < last; i++) {
		if(key > array[i]) {
			swap(array,i,j);
			j++;
		}
	}
	swap(array, last, j);
	return j;
}

// int partition (int arr[], int low, int high) 
// { 
//     int pivot = arr[high];
//     int i = (low - 1);
  
//     for (int j = low; j <= high- 1; j++) 
//     { 
//         if (arr[j] < pivot) 
//         { 
//             i++;
//             swap(arr,i,j); 
//         } 
//     } 
//     swap(arr,i + 1,high); 
//     return (i + 1); 
// } 

void quicksort(int* array, int first, int last) {
	if(last > first) {
		int pivot = partition(array, first, last);
		quicksort(array, first, pivot-1);
		quicksort(array, pivot+1, last);
	}
}
// void quicksort(int arr[], int low, int high) 
// { 
//     if (low < high) 
//     { 
//         int pi = partition(arr, low, high); 
//         quicksort(arr, low, pi - 1); 
//         quicksort(arr, pi + 1, high); 
//     } 
// } 
  

int readfile(char *filename_input, int **arrayptr)
{
    FILE *fptr;
    char filename[150];
    char stringbuf[50];
    int i = 0;
    int buf;
    strcpy(filename, filename_input);
    if ((fptr = fopen(filename, "r")) == NULL)
    {
        printf("This file is not available.");
        exit(1);
    }
    // deciding size of array
    while ((fscanf(fptr, "%d ", &buf)) != EOF)
    {
        i++;
    }

    // insert elements to memory-allocated array
    *arrayptr = (int *)malloc((i + 1) * sizeof(int));
    rewind(fptr);

    i = 0;
    while ((fscanf(fptr, "%d ", &buf)) != EOF)
    {
        (*arrayptr)[i++] = buf;
    }
    fclose(fptr);
    return i - 1;
}
void print_array(int *array, int last)
{
    int i;
    printf("\n-----------------------------------------------");
    for (int i = 0; i <= last; i++)
    {
        printf("%d ", array[i]);
        if ((i + 1) % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n-----------------------------------------------\n");
}

void write_file_array(char *output_name, int *array, int last)
{
    FILE *fptw = fopen(output_name, "w");
    for (int i = 0; i <= last; i++)
    {
        fprintf(fptw, "%d ", array[i]);
    }
    fclose(fptw);
}

int main(int argc, char* argv[]) {
	int* a;
	int** aptr = &a;
	int first = 0;
	int last = readfile(argv[1], aptr);
    clock_t start, end;
	start = clock();
	quicksort(a, first, last);
	end = clock();

	printf("%.3lf msec have taken for sorting.", (double)end-start);
    write_file_array(argv[2], a, last);
}