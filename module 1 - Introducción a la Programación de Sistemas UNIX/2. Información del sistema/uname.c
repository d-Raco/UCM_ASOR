#include <stdio.h>			/* perror(3), printf(3) */
#include <sys/utsname.h>	/* uname(2) */

/* gcc -Wall -g uname.c -o uname */

int main() {
   	struct utsname buf;

   	if(uname(&buf) < 0){
   		perror("Error in uname");
   		return -1;
   	}

   	printf("Nombre del sistema operativo: %s\n", buf.sysname);
   	printf("Hostname del nodo de red de la máquina: %s\n", buf.nodename);
   	printf("Versión del sistema operativo: %s\n", buf.release);
   	printf("Fecha de compilación del sistema operativo: %s\n", buf.version);
   	printf("Tipo de máquina: %s\n", buf.machine);

   	return 0;
}
