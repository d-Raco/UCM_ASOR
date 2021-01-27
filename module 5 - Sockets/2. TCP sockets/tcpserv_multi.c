#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
 
/* gcc -Wall -g tcpserv_multi.c -o tcpserv_multi */
 
#define MAX 80
 
int main(int argc, char **argv) {
    struct addrinfo *res;
    struct addrinfo hints;
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    int sock, socktcp;
    char buff[MAX];
    int nr_bytes;
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    int out = 0;
    pid_t pid;
 
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
 
    bind(sock, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
 
    listen(sock, 5);
 
    while(1) {
        socktcp = accept(sock, (struct sockaddr *) &addr, &addrlen);
        pid = fork();
        
        if(pid == 0) {
            getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
            printf("[%i] Connection from Host:%s Port:%s\n", getpid(), host, serv);
 
            while(!out) {
                while((nr_bytes = recv(socktcp, buff, MAX, 0))) {
                    buff[nr_bytes] = '\0';
                    printf("\tMensaje: %s", buff);
 
                    if (strncmp(buff, "Q", strlen(buff)-1) == 0) {
                        out = 1;
                        printf("[%i] Conexión terminada...\n", getpid());
                        strcpy(buff, " ");
                    }
 
                    send(socktcp, buff, nr_bytes, 0);
                }
            }
            close(socktcp); 
            return 0;
        }
    }
    close(sock);
 
    return 0;
}
