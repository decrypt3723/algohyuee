#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 int main(){
	 srand(time(NULL));
	 int a = rand();
	 srand(time(NULL));
	 int range = 10;
	 int p = (RAND_MAX*rand() + a) % (range+1);
	 printf("%d", p);

}
