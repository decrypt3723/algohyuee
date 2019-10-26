#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void swap(int *a, int input1, int input2)
{
    int temp;
    temp = a[input1];
    a[input1] = a[input2];
    a[input2] = temp;
}

int readfile(char *filename_input, int **arrayptr)
{
    FILE *fptr;
    char filename[50];
    char stringbuf[50];
    int i = 0;
    strcpy(filename, filename_input);
    if ((fptr = fopen(filename, "r")) == NULL)
    {
        printf("This file is not available.");
        exit(1);
    }
    // deciding size of array
    while ((fscanf(fptr, "%s ", stringbuf)) != EOF)
    {
        i++;
    }

    // insert elements to memory-allocated array
    *arrayptr = (int *)malloc((i + 1) * sizeof(int));
    rewind(fptr);

    i = 0;
    while ((fscanf(fptr, "%s ", stringbuf)) != EOF)
    {
        (*arrayptr)[i++] = atoi(stringbuf);
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

int partition(int* array, int first, int last) {
	int pivot = rand() % (last - first + 1);
	int key = array[pivot + first];
	int j = first;
	swap(array, last, pivot + first);
	for(int i = first; i < last; i++) {
		if(key > array[i]) {
			swap(array,i,j);
			j++;
		}
	}
	swap(array, last, j);
	return j;
}

void quicksort_sequential(int* arr, int last) { 
    int* stack = (int*)malloc(sizeof(int)*(last + 1)); 
    int top = -1;
    int left = 0;
    int right = last;
  
    stack[++top] = left; 
    stack[++top] = right; 
  
    while (top >= 0) { 
        right = stack[top--]; 
        left = stack[top--]; 
        int p = partition(arr, left, right); 
        if (p - 1 > left) { 
            stack[++top] = left; 
            stack[++top] = p - 1; 
        } 
        if (p + 1 < right) { 
            stack[++top] = p + 1; 
            stack[++top] = right; 
        } 
    }
    free(stack);
}

int main(int argc, char* argv[]) {
    int* a;
    int** aptr = &a;
    int last = readfile(argv[1], aptr);
    clock_t start, end;

    start = clock();
    quicksort_sequential(a, last);
    end = clock();
    printf("%.3lf msec have taken for sorting.", (double)end-start);
    write_file_array(argv[2], a, last);
}