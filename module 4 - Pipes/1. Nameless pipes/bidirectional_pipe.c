#include <stdio.h>		/* printf(3) */
#include <unistd.h>		/* fork(2), pipe(2), read(2), write(2), close(2), sleep(3) */
#include <sys/types.h>	/* fork(2) */

/* gcc -Wall -g bidirectional_pipe.c -o bidirectional_pipe */

#define MAX 20

int main() {
	pid_t child_pid;
	int p_h[2], h_p[2];
	char buf[MAX];
	int nr_bytes, cnt = 0;
	char confirm = 'l';

	pipe(p_h); /* Parent -> Child */
	pipe(h_p); /* Child -> Parent */

	child_pid = fork();

	switch(child_pid) {
	case 0:
		/* Child process */

		close(p_h[1]);
		close(h_p[0]);

		while(cnt < 10) {
			/* Redirect the reading end fd of the p_h pipe to stdout */
			nr_bytes = read(p_h[0], buf, MAX);
			write(1, buf, nr_bytes);
			sleep(1);
			/* Send confirmation to the other side */
			if(cnt == 9) 
				confirm = 'q';
			write(h_p[1], &confirm, 1);
			cnt++;
		}

		close(p_h[0]);
		close(h_p[1]);

		break;
	default:
		/* Parent process */

		close(p_h[0]);
		close(h_p[1]);

		while(confirm != 'q') {
			/* Redirect stdin to the writing end fd of the p_h pipe */
			nr_bytes = read(0, buf, MAX);
			write(p_h[1], buf, nr_bytes);
			/* Wait until confirmation from the other side */
			read(h_p[0], &confirm, 1);
		}

		close(p_h[1]);
		close(h_p[0]);

		break;
	}

	return 0;
}