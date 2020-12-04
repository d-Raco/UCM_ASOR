#include <stdio.h>		  /* perror(3), printf(3) */
#include <sys/types.h>  /* getuid(2), getpwuid(3) */
#include <unistd.h>     /* getuid(2) */
#include <pwd.h>        /* getpwuid(3) */

/* gcc -Wall -g userDesc.c -o userDesc */


int main() {
	uid_t id;
  struct passwd *user;

  id = getuid();

  if((user = getpwuid(id)) < 0){
   perror("Error in getpwuid");
   return -1;
  }

  printf("User name: %s\n", user->pw_name);
  printf("Home directory: %s\n", user->pw_dir);  
  printf("User description: %s\n", user->pw_gecos);

   return 0;
}
