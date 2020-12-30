#include <sys/types.h>	/* open(2) */
#include <sys/stat.h>	/* open(2) */
#include <fcntl.h>		/* open(2) */
#include <unistd.h>		/* close(2), dup2(2) */
#include <stdio.h>		/* printf(3), fprintf(3), perror(3) */

/* gcc -Wall -g stderr_redirection.c -o stderr_redirection */

int main(int argc, char **argv){
	int fd;

	if(argc < 2 || argc > 2){
		fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
		return -1;
	}

	if ((fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0777)) < 0) {
		perror("open");
		return -1;
	}

	if (dup2(fd, 1) < 0) {
		perror("dup2");
		return -1;
	}

   if (dup2(fd, 2) < 0) {
      perror("dup2");
      return -1;
   }

	printf("Hi, this is going to be redirected\nfrom stdout to the file.\n");
   fprintf(stderr, "Trying out the errors\n");
   printf("To see if it's fine\n");
   fprintf(stderr, "Bye!\n");

	if (close(fd) < 0) {
		perror("close");
		return -1;
	}

	return 0;
}