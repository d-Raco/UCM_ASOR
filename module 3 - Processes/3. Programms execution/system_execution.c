#include <stdio.h>		/* printf(3), perror(3) */
#include <stdlib.h>		/* system(3) */

/* gcc -Wall -g system_execution.c -o system_execution */

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Invalid number of arguments.\nUsage: ./system_execution \"<programm>\"\n");
		return -1;
	}

	system(argv[1]);

	printf("The command finished it's execution.\n");

   	return 0;
}
