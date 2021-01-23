#include <stdio.h>			/* printf(3), fprintf(3) */
#include <unistd.h>			/* fork(2), dup2(2), execvp(3), pipe(2), close(2) */
#include <sys/types.h>		/* fork(2) */

/* gcc -Wall -g pipe.c -o pipe */

int main(int argc, char **argv) {
	pid_t child_pid;
	char *command[3];
	int pipe_fd[2];

	if (argc != 5) {
		fprintf(stderr, "Invalid number of arguments.\nUsage: ./pipe <command1> <argument1> <command2> <argument2>\n");
		return -1;
	}

	pipe(pipe_fd);

	child_pid = fork();

	switch(child_pid) {
	case 0:
		/* Child process */

		/* Redirect stdin to the reading end fd of the pipe */
		dup2(pipe_fd[0], 0);

		/* Close unnecessary file descriptors */
		close(pipe_fd[0]);
		close(pipe_fd[1]);

		command[0] = argv[3];
		command[1] = argv[4];
		command[2] = NULL;
		execvp(command[0], command);

		break;
	default:
		/* Parent process */

		/* Redirect stdout to the writing end fd of the pipe */
		dup2(pipe_fd[1], 1);

		/* Close unnecessary file descriptors */
		close(pipe_fd[0]);
		close(pipe_fd[1]);

		command[0] = argv[1];
		command[1] = argv[2];
		command[2] = NULL;
		execvp(command[0], command);

		break;
	}

	return 0;
}