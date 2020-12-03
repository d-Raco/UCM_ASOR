#include <stdio.h>		/* perror(3), printf(3) */
#include <sys/types.h>  /* setuid(2) */
#include <unistd.h>		/* setuid(2) */
#include <errno.h>		/* errno */

/* gcc -Wall -g setuidErrno.c -o setuidErrno */


int main() {
   if(setuid(0) < 0){
	   perror("Error in setuid");
	   printf("Errno value: %d\n", errno);
	   return -1;
   }

   return 0;
}
