#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
 
/* gcc -Wall -g udpclient.c -o udpclient */
 
#define MAX 80
 
int main(int argc, char **argv) {
    struct addrinfo *res;
    struct addrinfo hints;
    int sock;
   int nr_bytes;
    char buff[MAX];
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
 
    if (argc != 4) {
        fprintf(stderr, "Usage: ./udpserv <address> <port> <t|d|q>");
        return -1;
    }
 
    memset(&hints, 0, sizeof(struct addrinfo));
 
    hints.ai_flags = AI_PASSIVE; // Return 0.0.0.0 o ::
    hints.ai_family = AF_UNSPEC; // IPv4 o IPv6
    hints.ai_socktype = SOCK_DGRAM;
    
    if (getaddrinfo(argv[1], argv[2], &hints, &res) < 0) {
        fprintf(stderr, "Error in getaddrinfo(): Name or service unknown\n");
        return -1;
    }
 
    sock = socket(res->ai_family, res->ai_socktype, 0);
 
    if (connect(sock, (struct sockaddr *) res->ai_addr, res->ai_addrlen) < 0) {
       fprintf(stderr, "Error while connecting with the socket\n");
       return -1;
   }
 
   strcpy(buff, argv[3]);
   strcat(buff, "\n");
 
   if (sendto(sock, buff, strlen(buff), 0, (struct sockaddr *) res->ai_addr, res->ai_addrlen) < 0) {
       fprintf(stderr, "Error sending data to the socket\n");
       return -1;
   }
   printf("%s\n", argv[3]);
 
   nr_bytes = recvfrom(sock, buff, MAX, 0, (struct sockaddr *) &addr, &addrlen);
   buff[nr_bytes] = '\0';
 
   printf("%s\n", buff);
 
    close(sock);
 
    return 0;
}
