#include <stdio.h>			/* printf(3), perror(3) */
#include <unistd.h>			/* write(2), close(2) */
#include <sys/types.h>		/* open(2) */
#include <sys/stat.h>		/* open(2) */
#include <fcntl.h>			/* open(2) */
#include <sys/select.h>		/* select(2) */

/* gcc -Wall -g mux.c -o mux 
   mkfifo fifo1
   mkfifo fifo2
*/

#define MAX 256

int main() {
	int fifo1, fifo2, nfds, mods, nr_bytes;
	char buffer[MAX];
	fd_set set;
	struct timeval timeout;

	while(1) {
		if((fifo1 = open("fifo1", O_RDONLY | O_NONBLOCK)) < 0) {
			perror("open");
			return -1;
		}

		if((fifo2 = open("fifo2", O_RDONLY | O_NONBLOCK)) < 0) {
			perror("open");
			return -1;
		}

		/* Initialize the set as empty */
		FD_ZERO(&set);
		/* Add both file descriptors to the set */
		FD_SET(fifo1, &set);
		FD_SET(fifo2, &set);

		timeout.tv_sec = 2;
	 	timeout.tv_usec = 0;

		/* Get the value of the biggest file descriptor of the set plus 1 */
		if(fifo1 > fifo2)
			nfds = fifo1 + 1;
		else
			nfds = fifo2 + 1;

		/* Monitors multiple file descriptors.
		   In this case we are only interested in read-only file descriptors,
		   so the rest sets are NULL. timeout = 2.
		*/
		mods = select(nfds, &set, NULL, NULL, &timeout);

		if (mods == -1)
			perror("select");
		else if (mods) {
			nr_bytes = read(fifo1, buffer, MAX-1);
			buffer[nr_bytes] = '\0';
			if(nr_bytes != 0)
				printf("New data of fifo1: %s\n", buffer);
			nr_bytes = read(fifo2, buffer, MAX-1);
			buffer[nr_bytes] = '\0';
			if(nr_bytes != 0)
				printf("New data of fifo2: %s\n", buffer);
		} 
		else {
			printf("No new data in 2 secs\n");
		}

		close(fifo1);
		close(fifo2);
	}

	return 0;
}