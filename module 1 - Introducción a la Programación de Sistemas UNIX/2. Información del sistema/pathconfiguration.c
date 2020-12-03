#include <stdio.h>	/* perror(3), printf(3) */
#include <unistd.h>	/* pathconf(3) */

/* gcc -Wall -g pathconfiguration.c -o pathconfiguration */

int main() {
   const char *s = "./pathconfiguration.c";
      long int n;	

      if((n = pathconf(s, _PC_LINK_MAX)) < 0){
   		perror("Error in pathconf while accessing _PC_LINK_MAX");
   		return -1;
   	}
      printf("Maximum number of links: %ld\n", n);

      if((n = pathconf(s, _PC_PATH_MAX)) < 0){
         perror("Error in pathconf while accessing _PC_PATH_MAX");
         return -1;
      }
      printf("Maximum path length: %ld\n", n);

      if((n = pathconf(s, _PC_NAME_MAX)) < 0){
         perror("Error in pathconf while accessing _PC_NAME_MAX");
         return -1;
      }
      printf("Maximum file name length: %ld\n", n);

   	return 0;
}