#include <stdio.h>	/* perror(3), printf(3) */
#include <unistd.h>	/* sysconf(3) */

/* gcc -Wall -g sysconfiguration.c -o sysconfiguration */

int main() {
      long int n;	

      if((n = sysconf(_SC_ARG_MAX)) < 0){
   		perror("Error in sysconf while accessing _SC_ARG_MAX");
   		return -1;
   	}
      printf("Maximum argument length: %ld\n", n);

      if((n = sysconf(_SC_CHILD_MAX)) < 0){
         perror("Error in sysconf while accessing _SC_CHILD_MAX");
         return -1;
      }
      printf("Maximum number of childs: %ld\n", n);

      if((n = sysconf(_SC_OPEN_MAX)) < 0){
         perror("Error in sysconf while accessing _SC_OPEN_MAX");
         return -1;
      }
      printf("Maximum number of open files: %ld\n", n);

   	return 0;
}