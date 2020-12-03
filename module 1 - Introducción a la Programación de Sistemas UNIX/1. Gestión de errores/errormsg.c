#include <string.h>	/* strerror(3) */
#include <stdio.h>	/* printf(3) */

/* gcc -Wall -g errormsg.c -o errormsg */

#define NUM_ERRORS 255

int main() {
   	for(int i = 0; i < NUM_ERRORS; ++i)
   		printf("Error %d - %s\n", i, strerror(i));

   	return 0;
}
