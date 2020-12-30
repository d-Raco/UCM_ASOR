#include <stdio.h>			/* printf(3), perror(3) */
#include <unistd.h>			/* getpid(2), getppid(2), getpgid(2), getsid(2), getcwd(3), getrlimit(2) */
#include <sys/types.h>		/* getpid(2), getppid(2), getpgid(2), getsid(2) */	
#include <sys/time.h>		/* getrlimit(2) */
#include <sys/resource.h>	/* getrlimit(2) */

/* gcc -Wall -g print_process.c -o print_process */

#define SIZE 100

int main() {
	pid_t pid, ppid, pgid, sid;
	char cwd[SIZE];
	struct rlimit rlim;

	pid = getpid();
	ppid = getppid();

	if ((pgid = getpgid(pid)) < 0) {
		perror("getpgid");
		return -1;
	}

	if ((sid = getsid(pid)) < 0) {
		perror("getsid");
		return -1;
	}

	if (getrlimit(RLIMIT_OFILE, &rlim) < 0) {
		perror("getrlimit");
		return -1;
	}

	if (getcwd(cwd, SIZE) == NULL) {
		perror("getcwd");
		return -1;
	}

	printf("Pid: %d.\n", pid);
	printf("Ppid: %d.\n", ppid);
	printf("Pgid: %d.\n", pgid);
	printf("Sid: %d.\n", sid);
	printf("Maximum number of opened files: %lu.\n", rlim.rlim_max);
	printf("Current working directory: %s.\n", cwd);

   	return 0;
}
