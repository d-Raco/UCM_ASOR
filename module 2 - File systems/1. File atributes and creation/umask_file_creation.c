#include <sys/types.h>	/* open(2), umask(2) */
#include <sys/stat.h>	/* open(2), umask(2) */
#include <fcntl.h>		/* open(2) */
#include <unistd.h>		/* close(2) */
#include <stdio.h>		/* perror(3) */

/* gcc -Wall -g umask_file_creation.c -o umask_file_creation */

int main() {
   int fd;

	umask(027);
	if (fd = open("fichero", O_CREAT, 0645) < 0){
		perror("open");
		return -1;
	}

	if (close(fd) < 0){
		perror("close");
		return -1;
	}
	
	return 0;
}
