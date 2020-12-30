#include <stdio.h>		/* printf(3), perror(3) */
#include <signal.h>		/* sigaction(2), sigisuspend(2) */	

/* gcc -Wall -g sighandler.c -o sighandler */

int sigint = 0;
int sigtstp = 0;

void handler(int signal) {
	if (signal == SIGINT)
		sigint++;
	else if (signal == SIGTSTP)
		sigtstp++;
}

int main() {
	struct sigaction act;
	sigset_t set;

	sigaction(SIGINT, NULL, &act);
	act.sa_handler = handler;

	if (sigaction(SIGINT, &act, NULL) < 0) {
		perror("sigaction");
		return -1;
	}

	if (sigaction(SIGTSTP, &act, NULL) < 0) {
		perror("sigaction");
		return -1;
	}

	while(sigint + sigtstp < 10)
		sigsuspend(&set);

	printf("\nSIGINT: %d times.\n", sigint);
	printf("SIGSTP: %d times.\n", sigtstp);

	return 0;
}
