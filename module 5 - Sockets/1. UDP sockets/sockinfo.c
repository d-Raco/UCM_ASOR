#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
 
/* gcc -Wall -g sockinfo.c -o sockinfo */
 
int main(int argc, char **argv) {
    struct addrinfo *res;
    char host[NI_MAXHOST];
 
    if(argc != 2) {
        fprintf(stderr, "Usage: ./sockinfo <hostname>\n");
        return -1;
    }
 
    if (getaddrinfo(argv[1], NULL, NULL, &res) < 0) {
        fprintf(stderr, "Error in getaddrinfo(): Name or service unknown\n");
        return -1;
    }
    
    while (res != NULL) {
        getnameinfo(res->ai_addr, res->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
        printf("%s\t%d\t%d\n", host, res->ai_family, res->ai_socktype);
        /* IP, Protocol family, Socket type */
        
        res = res->ai_next;
    }
 
    return 0;
}
