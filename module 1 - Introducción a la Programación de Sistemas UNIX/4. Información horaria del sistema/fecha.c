#include <stdio.h> 	/* perror(3), printf(3) */
#include <time.h>	/* time(2), localtime(3), strftime(3) */

/* gcc -Wall -g fecha.c -o fecha */

#define MAX 50

int main() {
	struct tm *timeYear;
	time_t secs;
	char str[MAX];

  	if((time(&secs)) < 0){
   		perror("Error in time");
    	return -1;
  	}

  	if((timeYear = localtime(&secs)) == NULL){
		perror("Error in localtime");
		return -1;
	}

	if(strftime(str, MAX, "%A, %e de %B de %G, %H:%M", timeYear) == 0){
		perror("Error in strftime");
		return -1;
	}

	printf("%s\n", str);

	return 0;
}