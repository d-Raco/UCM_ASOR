#include <stdio.h>  /* perror(3), printf(3) */
#include <time.h>   /* time(2) */

/* gcc -Wall -g epochSecs.c -o epochSecs */


int main() {
	time_t secs;

  	if((secs = time(NULL)) < 0){
   		perror("Error in time");
    	return -1;
  	}

 	printf("Seconds since Epoch: %ld\n", secs);

   	return 0;
}
