#include <stdio.h>		/* printf(3), perror(3) */
#include <unistd.h>		/* execvp(3) */
#include <string.h>		/* strtok(3) */

/* gcc -Wall -g execvp_execution.c -o execvp_execution */

int main(int argc, char **argv) {
	int i = 1;
	char *comm[10];
	
	if (argc != 2) {
		printf("Invalid number of arguments.\nUsage: ./execvp_execution \"<programm>\"\n");
		return -1;
	}

	comm[0] = strtok(argv[1], " ");
	while(comm[i] != NULL)
		comm[i++] = strtok(NULL, " ");

	execvp(comm[0], comm);

	printf("The command finished it's execution.\n");

   	return 0;
}
