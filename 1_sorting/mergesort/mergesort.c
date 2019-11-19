#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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

void merge(int* a, int q, int r, int middle) {
	int i = q;
	int j = middle+1;
	int k = 0;
	int b[r-q+1];
	while( k < (r-q+1)) {
		if(i == (middle+1)) {
			b[k] = a[j];
			j++;
		}
		else if (j == (r+1)) {
			b[k] = a[i];
			i++;
		}
		else if (a[i] <= a[j]) {
			b[k] = a[i];
			i++;
		}
		else {
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

void mergesort(int* a, int q, int r) {
	int middle = ((q+r) / 2);
	if (q < r) {
		mergesort(a, q, middle);
		mergesort(a, middle+1, r);
		merge(a,q,r,middle);
	}
}

int main (int argc, char* argv[]) {
	int* a;
	int** aptr = &a;
	int first = 0;
	int last = readfile(argv[1], aptr);
	clock_t start, end;

	start = clock();
	mergesort(a,first,last);
	end = clock();

	printf("%.3lf msec have taken for sorting.", (double)end-start);
    write_file_array(argv[2], a, last);
    free(a);
}