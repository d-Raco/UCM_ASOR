#include <stdio.h>			/* printf(3), perror(3), fprintf(3) */
#include <unistd.h>			/* getpid(2), getppid(2), setsid(2), chdir(2), getrlimit(2), fork(2), exit(2), execvp(3), close(2), dup2(2) */
#include <sys/types.h>		/* getpid(2), getppid(2), setsid(2), fork(2), wait(2), open(2) */	
#include <stdlib.h>			/* exit(2) */
#include <wait.h>			/* wait(2) */
#include <string.h>			/* strtok(3) */
#include <sys/stat.h>   	/* open(2) */
#include <fcntl.h>      	/* open(2) */

/* gcc -Wall -g daemon.c -o daemon */

int main(int argc, char **argv) {
	char *comm[3];
	pid_t pid, child_pid, sid;
	char *dir = "/tmp";
	int status, fd0, fd1, fd2;
	
	if (argc != 2) {
		fprintf(stderr, "Invalid number of arguments.\nUsage: ./daemon \"<programm>\"\n");
		return -1;
	}
	
	child_pid = fork();
	switch (child_pid) {
	case -1:
		perror("fork");
		exit(1);
	case 0:
		pid = getpid();
		sid = setsid();

		if (chdir(dir) < 0) {
			perror("chdir");
			return -1;
		}

		printf("Child process %i (parent: %i).\n", pid, getppid());
		printf("Sid: %d.\n", sid);
		printf("Current working directory: %s.\n", dir);

		comm[0] = strtok(argv[1], " ");
		comm[1] = strtok(NULL, " ");
		comm[2] = NULL;

		if ((fd0 = open("/tmp/daemon.out", O_CREAT | O_TRUNC | O_RDWR, 0777)) < 0) {
		    perror("open");
		    return -1;
		}

		if ((fd1 = open("/tmp/daemon.out", O_CREAT | O_TRUNC | O_RDWR, 0777)) < 0) {
		    perror("open");
		    return -1;
		}

		if ((fd2 = open("/tmp/daemon.err", O_CREAT | O_TRUNC | O_RDWR, 0777)) < 0) {
		    perror("open");
		    return -1;
		}

		if (dup2(fd0, 0) < 0) {
		    perror("dup2");
		    return -1;
		}

		if (dup2(fd1, 1) < 0) {
		    perror("dup2");
		    return -1;
		}

		if (dup2(fd2, 2) < 0) {
		    perror("dup2");
		    return -1;
		}

		execvp(comm[0], comm);

		if (close(fd0) < 0) {
			perror("close");
			return -1;
		}

		if (close(fd1) < 0) {
			perror("close");
			return -1;
		}

		if (close(fd2) < 0) {
			perror("close");
			return -1;
		}

		break;
	default:
		pid = getpid();

		wait(&status);

		printf("Parent process %i (child: %i).\n", pid, child_pid);
		break;
	}

   	return 0;
}
