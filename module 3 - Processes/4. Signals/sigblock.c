#include <stdio.h>		/* printf(3), perror(3), fprintf(3) */
#include <signal.h>		/* sigismember(3), sigpending(2), sigemptyset(3), sigaddset(3), sigprocmask(2) */	
#include <unistd.h>		/* sleep(3) */
#include <stdlib.h>		/* setenv(3), getenv(3), atoi(3) */

/* gcc -Wall -g sigblock.c -o sigblock */

int main() {
	sigset_t blk_set, pending;
	
	if (sigemptyset(&blk_set) < 0) {
		perror("sigemptyset");
		return -1;
	}

	if (sigaddset(&blk_set, SIGINT) < 0) {
		perror("sigaddset");
		return -1;
	}

	if (sigaddset(&blk_set, SIGTSTP) < 0) {
		perror("sigaddset");
		return -1;
	}

	if (sigprocmask(SIG_BLOCK, &blk_set, NULL) < 0) {
		perror("sigprocmask");
		return -1;
	}

	/* Protected code */
	setenv("SLEEP_SECS", "6", 1);
	sleep(atoi(getenv("SLEEP_SECS")));

	if (sigpending(&pending) < 0) {
		perror("sigpending");
		return -1;
	}

	if (sigismember(&pending, SIGINT) == 1) {
		printf("SIGINT received\n");
		sigdelset(&blk_set, SIGINT);
	}

	if (sigismember(&pending, SIGTSTP) == 1)
		printf("SIGTSTP received\n");


	if (sigprocmask(SIG_UNBLOCK, &blk_set, NULL) < 0) {
		perror("sigprocmask");
		return -1;
	}

	printf("Done\n");

	return 0;
}
