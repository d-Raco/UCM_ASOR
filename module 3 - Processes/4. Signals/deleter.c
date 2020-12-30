#include <stdio.h>		/* printf(3), perror(3) */
#include <signal.h>		/* sigfillset(3), sigismember(3), sigpending(2), sigemptyset(3), sigprocmask(2) */	
#include <stdlib.h>		/* atoi(3) */
#include <unistd.h>		/* sleep(3), unlink(2) */

/* gcc -Wall -g deleter.c -o deleter */

int main(int argc, char **argv) {
	sigset_t set, pending;
	int secs, delete = 1;

	if (argc != 2) {
		printf("Invalid number of arguments.\nUsage: ./deleter \"<seconds>\"\n");
		return -1;
	}

	if (sigfillset(&set) < 0) {
		perror("sigfillset");
		return -1;
	}

	if (sigprocmask(SIG_BLOCK, &set, NULL) < 0) {
		perror("sigprocmask");
		return -1;
	}

	/* Protected code */
	secs = atoi(argv[1]);

	sleep(secs);

	if (sigpending(&pending) < 0) {
		perror("sigpending");
		return -1;
	}

	if (sigismember(&pending, SIGUSR1) == 1) {
		printf("SIGUSR1 received\n");
		delete = 0;
	}

	if (sigemptyset(&set) < 0) {
		perror("sigemptyset");
		return -1;
	}

	if (sigprocmask(SIG_UNBLOCK, &set, NULL) < 0) {
		perror("sigprocmask");
		return -1;
	}

	if (delete == 1) {
		printf("Deleting file.\n");
		unlink(argv[0]);
	}
	else
		printf("Aborting file deletion.\n");


	return 0;
}
