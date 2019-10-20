#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int input1, int input2);

int main() {
	int a[1000];
	int local_max;
	int first = 0;
	int last;
	int temp;



	for(int j = last; j > first; j--) {
		local_max = 0;
		for(int i = first i < j; i++) {
			if(a[i] > local_max) {
				local_max = i;
			}
		}
		swap(a, i,  local_max); 
	}

	for(int i = first; i <= last; i++) {
		printf("%d ", a[i]);
		if(i % 10 == 0) {
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
