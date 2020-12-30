#include <sys/types.h>	/* stat(2) */
#include <sys/stat.h>	/* stat(2) */
#include <sys/unistd.h>	/* stat(2) */
#include <stdio.h>		/* printf(3), fprintf(3), perror(3) */
#include <time.h>		/* localtime(3) */

/* gcc -Wall -g stat.c -o stat */

int main(int argc, char **argv) {
	struct tm *time;
	struct stat buf;

	if (argc < 2 || argc > 2){
		fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
		return -1;
	}

	if (lstat(argv[1], &buf) < 0){
		perror("lstat");
		return -1;
	}

	if ((time = localtime(&buf.st_atime)) == NULL){
		perror("localtime");
		return -1;
	}

	printf("Major an minor: %d, %d\n", major(buf.st_rdev), minor(buf.st_rdev));
	printf("i-node number: %lu\n", buf.st_ino);
	printf("File type: ");
	switch (buf.st_mode & S_IFMT) {
		case S_IFBLK:	printf("Character device\n");		break;
		case S_IFCHR:	printf("Block device\n");			break;
		case S_IFDIR:	printf("Directory\n");				break;
		case S_IFIFO:	printf("FIFO (named pipe)\n");		break;
		case S_IFLNK:	printf("Symbolic link\n");			break;
		case S_IFREG:	printf("Regular file\n");			break;
		case S_IFSOCK:	printf("Socket\n");					break;
		default:		printf("Unknown\n");				break;
	}

/*
	if (S_ISCHR(buf.st_mode)) 		printf("Character device\n");
	else if (S_ISBLK(buf.st_mode)) 	printf("Block device\n");
	else if (S_ISDIR(buf.st_mode)) 	printf("Directory\n");
	else if (S_ISFIFO(buf.st_mode)) printf("FIFO (named pipe)\n");
	else if (S_ISLNK(buf.st_mode)) 	printf("Symbolic link\n");
	else if (S_ISREG(buf.st_mode)) 	printf("Regular file\n");
	else if (S_ISSOCK(buf.st_mode)) printf("Socket\n");
*/
	printf("Last access time: %d:%d:%d\n", time->tm_hour, time->tm_min, time->tm_sec);

   	return 0;
}
