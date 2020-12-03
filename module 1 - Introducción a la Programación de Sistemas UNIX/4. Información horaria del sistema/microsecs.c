#include <stdio.h>  	/* perror(3), printf(3) */
#include <sys/time.h>   /* gettimeofday(2) */

/* gcc -Wall -g microsecs.c -o microsecs */


int main() {
	struct timeval before, after;

	if(gettimeofday(&before, NULL) < 0){
		perror("Error in gettimeofday");
		return -1;
	}

	for(int i = 0; i < 1000000; ++i){}

	if(gettimeofday(&after, NULL) < 0){
		perror("Error in gettimeofday");
		return -1;
	}

	printf("Microseconds lasted in a 1M loop: %ld\n", after.tv_usec - before.tv_usec);

	return 0;
}