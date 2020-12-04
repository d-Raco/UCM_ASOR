#include <stdio.h>		  /* perror(3), printf(3) */
#include <sys/types.h>  /* getuid(2) */
#include <unistd.h>     /* getuid(2) */

/* gcc -Wall -g uid.c -o uid */


int main() {
	uid_t id;

   id = getuid();
   printf("Real user id: %d\n", id);
   id = geteuid();
   printf("Effective user id: %d\n", id);

   return 0;
}
