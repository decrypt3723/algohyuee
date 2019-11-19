#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	FILE* fptr;
	FILE* fptrw;
	fptr = fopen(argv[1], "r");
	fptrw = fopen(argv[2], "w");
	int intbuf;
	char charbuf;
	while(fscanf(fptr, "%c ", &charbuf) != EOF) {
		fprintf(fptrw, "%d ", (int)(charbuf));
	}
}

