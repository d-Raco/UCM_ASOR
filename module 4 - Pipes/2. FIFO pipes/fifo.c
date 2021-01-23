#include <stdio.h>			/* printf(3), fprintf(3), perror(3) */
#include <unistd.h>			/* write(2), close(2) */
#include <sys/types.h>		/* open(2) */
#include <sys/stat.h>		/* open(2) */
#include <fcntl.h>			/* open(2) */
#include <string.h>			/* strlen(3) */

/* gcc -Wall -g fifo.c -o fifo 
   mkfifo fifopipe
*/

int main(int argc, char **argv) {
	int fd;

	if (argc != 2) {
		fprintf(stderr, "Invalid number of arguments.\nUsage: ./fifo <fifo_file>\n");
		return -1;
	}

	if((fd = open(argv[1], O_WRONLY)) < 0) {
		perror("open");
		return -1;
	}

	write(fd, argv[1], strlen(argv[1]));

	close(fd);

	return 0;
}