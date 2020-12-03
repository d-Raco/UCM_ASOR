#include <stdio.h>		/* perror(3) */
#include <sys/types.h>  /* setuid(2) */
#include <unistd.h>		/* setuid(2) */

/* gcc -Wall -g setuid.c -o setuid */


int main() {
   if(setuid(0) < 0){
	   perror("Error in setuid");
	   return -1;
   }

   return 0;
}
