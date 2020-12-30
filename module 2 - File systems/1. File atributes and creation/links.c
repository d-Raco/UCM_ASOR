#include <sys/types.h>	/* stat(2) */
#include <sys/stat.h>	/* stat(2) */
#include <sys/unistd.h>	/* stat(2), link(2), symlink(2) */
#include <stdio.h>		/* printf(3), perror(3) */
#include <string.h>		/* strchr(3), strcat(3), strcpy(3), strncpy(3) */

/* gcc -Wall -g links.c -o links */

int main(int argc, char **argv) {
	struct stat buf;
	char prestr[50], aux[50];
	char *p;

	if (argc < 2 || argc > 2){
		fprintf(stderr, "Usage: %s <pathname>.\n", argv[0]);
		return -1;
	}

	if (stat(argv[1], &buf) < 0){
		perror("stat");
		return -1;
	}

	if (!S_ISREG(buf.st_mode)) {
		printf("File must be a regular file.\n");
		return -1;
	}

	p = strchr(argv[1], '.');
	if(p != NULL){
		strncpy(prestr, argv[1], p-argv[1]);
		prestr[p-argv[1]] = '\0';
	}
	else
		strcpy(prestr, argv[1]);
	
	strcpy(aux, prestr);
	if (symlink(argv[1], strcat(prestr, ".sym")) < 0){
		perror("symlink");
		return -1;
	}

	if (link(argv[1], strcat(aux, ".hard")) < 0){
		perror("link");
		return -1;
	}

   	return 0;
}
