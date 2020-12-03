#include <stdio.h> 	/* perror(3), printf(3) */
#include <time.h>	/* localtime(3), time(2) */

/* gcc -Wall -g año.c -o año */

#define FIRST_YEAR 1900

int main() {
	struct tm *timeYear;
	time_t secs;

  	if((time(&secs)) < 0){
   		perror("Error in time");
    	return -1;
  	}

	if((timeYear = localtime(&secs)) == NULL){
		perror("Error in localtime");
		return -1;
	}

	printf("Year: %d\n", timeYear->tm_year + FIRST_YEAR);

	return 0;
}