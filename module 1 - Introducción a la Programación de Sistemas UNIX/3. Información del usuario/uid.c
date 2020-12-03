#include <stdio.h>		  /* perror(3), printf(3) */
#include <sys/types.h>  /* getuid(2) */
#include <unistd.h>     /* getuid(2) */

/* gcc -Wall -g uid.c -o uid */


int main() {
	uid_t id;

   if((id = getuid()) < 0){
	   perror("Error in getuid");
	   return -1;
   }
   printf("Real user id: %d\n", id);

    if((id = geteuid()) < 0){
	   perror("Error in geteuid");
	   return -1;
   }
   printf("Effective user id: %d\n", id);

   return 0;
}
