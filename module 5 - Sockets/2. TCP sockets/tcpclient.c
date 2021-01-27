#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
 
/* gcc -Wall -g tcpclient.c -o tcpclient */
 
#define MAX 80
 
int main(int argc, char **argv) {
    struct addrinfo *res;
    struct addrinfo hints;
    int sock;
   int nr_bytes;
    char buff[MAX];
 
    if (argc != 3) {
        fprintf(stderr, "Usage: ./udpserv <address> <port>");
        return -1;
    }
 
    memset(&hints, 0, sizeof(struct addrinfo));
 
    hints.ai_flags = AI_PASSIVE; // Return 0.0.0.0 o ::
    hints.ai_family = AF_UNSPEC; // IPv4 o IPv6
    hints.ai_socktype = SOCK_STREAM;
    
    if (getaddrinfo(argv[1], argv[2], &hints, &res) < 0) {
        fprintf(stderr, "Error in getaddrinfo(): Name or service unknown\n");
        return -1;
    }
 
    sock = socket(res->ai_family, res->ai_socktype, 0);
 
    if (connect(sock, (struct sockaddr *) res->ai_addr, res->ai_addrlen) < 0) {
       fprintf(stderr, "Error while connecting with the socket\n");
       return -1;
   }
 
    strcpy(buff, " \n");
    while (strncmp(buff, "Q", strlen(buff)-1) != 0) {
        nr_bytes = read(0, buff, MAX);
        buff[nr_bytes] = '\0';
        send(sock, buff, nr_bytes, 0);
 
        nr_bytes = recv(sock, buff, MAX, 0);
        buff[nr_bytes] = '\0';
        printf("%s", buff);
    }
 
    close(sock);
 
    return 0;
}
