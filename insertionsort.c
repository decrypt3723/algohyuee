#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int input1, int input2);
void array_shift(int* a, int shift_index, int array_last);

int main() {
	int a[1000];
	int key;	
	int first = 0;
	int last;	


	for(int j = first + 1; j <= last; j++) {
		key = a[j];		
		for(int i = j; i >= first; i--) {
			if(key >= a[i]) {	
				array_shift(a,i,j-1);								
				a[i] = key;
			}			

		}
	}
}

void swap(int* a, int input1, int input2) { 
	int temp;
	temp = a[input1];
	a[input1] = a[input2];
	a[input2] = temp;
}
void array_shift(int* a, int shift_first, int array_last) {
	for(int i = array_last; i >= shift_first; i--) {
		a[i+1] = a[i];
	}
}

