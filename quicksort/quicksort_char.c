#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void swap(char* a, int input1, int input2) {
	char temp;
	temp = a[input1];
	a[input1] = a[input2];
	a[input2] = temp;
}

int partition(char* array, int first, int last) {
	int pivot = rand() % (last - first + 1);
	char key = array[pivot + first];
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

void quicksort(char* array, int first, int last) {
	if(last > first) {
		int pivot = partition(array, first, last);
		quicksort(array, first, pivot-1);
		quicksort(array, pivot+1, last);
	}	
}

int readfile(char *filename_input, char **arrayptr)
{
    FILE *fptr;
    char filename[50];
    char charbuf;
    int i = 0;
    strcpy(filename, filename_input);
    if ((fptr = fopen(filename, "r")) == NULL)
    {
        printf("This file is not available.");
        exit(1);
    }
    // deciding size of array
    while ((fscanf(fptr, "%s ", &charbuf)) != EOF)
    {
        i++;
    }

    // insert elements to memory-allocated array
    *arrayptr = (char *)malloc((i + 1) * sizeof(char));
    rewind(fptr);

    i = 0;
    while ((fscanf(fptr, "%c ", &charbuf)) != EOF)
    {
        (*arrayptr)[i++] = charbuf;
    }
    fclose(fptr);
    return i - 1;
}
void print_array(char *array, int last)
{
    int i;
    printf("\n-----------------------------------------------");
    for (int i = 0; i <= last; i++)
    {
        printf("%c ", array[i]);
        if ((i + 1) % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n-----------------------------------------------\n");
}

void write_file_array(char *output_name, char *array, int last)
{
    FILE *fptw = fopen(output_name, "w");
    for (int i = 0; i <= last; i++)
    {
        fprintf(fptw, "%c ", array[i]);
    }
    fclose(fptw);
}

int main(int argc, char* argv[]) {
	srand((unsigned)time(NULL));
	char* a;
	char** aptr = &a;
	int first = 0;
	int last = readfile(argv[1], aptr);
    clock_t start, end;

	start = clock();
	quicksort(a, first, last);
	end = clock();

	printf("%.3lf msec have taken for sorting.", (double)end-start);
    write_file_array(argv[2], a, last);
}
