#include <sys/types.h>	/* open(2) */
#include <sys/stat.h>	/* open(2) */
#include <sys/file.h>   /* lockf(2) */
#include <fcntl.h>		/* open(2), fcntl(2) */
#include <unistd.h>		/* close(2), fcntl(2), sleep(3), write(2) */
#include <stdio.h>		/* printf(3), fprintf(3), perror(3) */
#include <time.h>       /* time(2), localtime(3), strftime(3) */
#include <string.h>     /* strlen(3) */

/* gcc -Wall -g locks.c -o locks */

#define MAX 50

int main(int argc, char **argv){
	int fd;
   struct flock lock;
   struct tm *timeYear;
   time_t secs;
   char str[MAX];

	if(argc < 2 || argc > 2) {
		fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
		return -1;
	}

	if ((fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0777)) < 0) {
		perror("open");
		return -1;
	}

   if (fcntl(fd, F_GETLK, &lock) < 0) {
      perror("open");
      return -1;
   }

   if (lock.l_type == F_UNLCK)
      printf("Cerrojo desbloqueado\n");
   else{
      printf("Cerrojo bloqueado\n");
      return 1;
   }

   if (lockf(fd, F_TLOCK, 0) < 0) {
      perror("lockf");
      return -1;
   }

   if ((time(&secs)) < 0) {
         perror("time");
      return -1;
   }

   if ((timeYear = localtime(&secs)) == NULL) {
      perror("localtime");
      return -1;
   }

   if (strftime(str, MAX, "%H:%M:%S", timeYear) == 0) {
      perror("strftime");
      return -1;
   }

   if (write(fd, &str, strlen(str)) < 0) {
      perror("write");
      return -1;
   }

   sleep(30);

   if (lockf(fd, F_ULOCK, 0) < 0) {
      perror("lockf");
      return -1;
   }

	if (close(fd) < 0) {
		perror("close");
		return -1;
	}

	return 0;
}