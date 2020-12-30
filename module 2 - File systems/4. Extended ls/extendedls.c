#include <sys/types.h>	/* stat(2), opendir(3), readdir(3), closedir(3) */
#include <sys/stat.h>	/* stat(2) */
#include <sys/unistd.h>	/* stat(2), readlink(2) */
#include <stdio.h>		/* printf(3), fprintf(3), perror(3) */
#include <dirent.h>		/* opendir(3), readdir(3), closedir(3) */
#include <string.h>		/* strcpy(3), stract(3) */

/* gcc -Wall -g extendedls.c -o extendedls */

#define MAX 50

int main(int argc, char **argv) {
	DIR *fd;
	struct dirent *file;
	struct stat buf;
	char aux[MAX], link[MAX];
	int len;
	off_t size = 0;

	if (argc < 2 || argc > 2) {
		fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
		return -1;
	}

	if ((fd = opendir(argv[1])) == NULL) {
		perror("opendir");
		return -1;
	}

	while((file = readdir(fd)) != NULL) {
		strcpy(aux, argv[1]);
		strcat(aux, "/");
		strcat(aux, file->d_name);

		if (lstat(aux, &buf) < 0){
			perror("lstat");
			return -1;
		}

		switch (buf.st_mode & S_IFMT) {
			case S_IFDIR:	printf("%s/\n", file->d_name);		break;
			case S_IFLNK:	
				if ((len = readlink(file->d_name, link, MAX)) < 0) {
					perror("readlink");
					return -1;
				}
				link[len] = '\0';
				printf("%s -> %s\n", file->d_name, link);		break;
			case S_IXUSR:	printf("%s*\n", file->d_name);		break;
			case S_IFREG:	printf("%s\n", file->d_name);		break;
			default:		printf("%s\n", file->d_name);		break;
		}

		if(!S_ISDIR(buf.st_mode))
			size += buf.st_size;
	}

	printf("Size: %ldKB\n", size / 1024);

	if (closedir(fd) < 0) {
		perror("closedir");
		return -1;
	}

   	return 0;
}
