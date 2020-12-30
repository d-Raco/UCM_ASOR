#include <stdio.h>			/* printf(3), perror(3) */
#include <unistd.h>			/* getpid(2), getppid(2), getpgid(2), setsid(2), chdir(2), getrlimit(2), fork(2), exit(2) */
#include <sys/types.h>		/* getpid(2), getppid(2), getpgid(2), setsid(2), fork(2), wait(2) */	
#include <sys/time.h>		/* getrlimit(2) */
#include <sys/resource.h>	/* getrlimit(2) */
#include <stdlib.h>			/* exit(2) */
#include <wait.h>			/* wait(2) */

/* gcc -Wall -g daemon_template.c -o daemon_template */

int main() {
	pid_t pid, child_pid, pgid, sid;
	char *dir = "/tmp";
	struct rlimit rlim;
	int status;
	
	child_pid = fork();
	switch (child_pid) {
	case -1:
		perror("fork");
		exit(1);
	case 0:
		pid = getpid();
		sid = setsid();

		if ((pgid = getpgid(pid)) < 0) {
			perror("getpgid");
			return -1;
		}

		if (getrlimit(RLIMIT_OFILE, &rlim) < 0) {
			perror("getrlimit");
			return -1;
		}

		if (chdir(dir) < 0) {
			perror("chdir");
			return -1;
		}

		printf("Child process %i (parent: %i).\n", pid, getppid());
		printf("Pgid: %d.\n", pgid);
		printf("Sid: %d.\n", sid);
		printf("Maximum number of opened files: %lu.\n", rlim.rlim_max);
		printf("Current working directory: %s.\n", dir);
		exit(0);

		break;
	default:
		pid = getpid();

		wait(&status);

		printf("Parent process %i (child: %i).\n", pid, child_pid);
		break;
	}

   	return 0;
}
