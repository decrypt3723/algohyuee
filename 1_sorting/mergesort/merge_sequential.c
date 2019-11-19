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

void mergesort_sequential(int* a, int last) {
    int k; // merge size
    last++;
    int middle, right;
    int i, j, m;
    int* b = (int*)calloc(last, sizeof(int));
    for (int k=1; k < last; k *= 2 ) {       
        for (int left=0; left+k < last; left += k*2 ) {
            middle = left + k;        
            right = middle + k;
            if (right > last) right = last; 
            m = left; i = left; j = middle; 
            while (i < middle && j < right) { 
                if (a[i] <= a[j]) {         
                    b[m] = a[i]; i++;
                } else {
                    b[m] = a[j]; j++;
                }
                m++;
            }
            while (i < middle) { 
                b[m]=a[i]; 
                i++; m++;
            }
            while (j < right) { 
                b[m]=a[j]; 
                j++; m++;
            }
            for (m=left; m < right; m++) { 
                a[m] = b[m]; 
            }
        }
    }
    free(b);
}

int main(int argc, char *argv[])
{
    int* a;
    int** aptr = &a;
    int last = readfile(argv[1], aptr);
    clock_t start, end;

    start = clock();
    mergesort_sequential(a, last);
    end = clock();
    printf("%.3lf msec have taken for sorting.", (double)end-start);
    write_file_array(argv[2], a, last);
    free(a);
}