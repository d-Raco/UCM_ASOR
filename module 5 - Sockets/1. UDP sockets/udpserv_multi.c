#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
 
 
/* gcc -Wall -g udpserv_multi.c -o udpserv_multi */
 
#define MAX 80
#define MAX_CONNECT 3
 
int main(int argc, char **argv) {
    struct addrinfo *res;
    struct addrinfo hints;
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    int sockUDP, nr_bytes, out = 0, i, status;
    int yes = 1;
    char buff[MAX];
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    time_t secs;
    pid_t pid, rpid;
 
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
 
    sockUDP = socket(res->ai_family, res->ai_socktype, 0);
 
    setsockopt(sockUDP, SOL_SOCKET, SO_REUSEADDR, (const void *)&yes, sizeof(int));
 
    bind(sockUDP, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
 
    listen(sockUDP, MAX_CONNECT);
 
    for (i = 0;  i < MAX_CONNECT && !out; ++i) {
        int sock = accept(sockUDP, (struct sockaddr *) &addr, &addrlen);
                    
        pid = fork();
        if (pid == 0) {
            while (!out) {
                nr_bytes = recvfrom(sock, buff, MAX, 0, (struct sockaddr *) &addr, &addrlen);
                buff[nr_bytes] = '\0';
 
                getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
 
                printf("[%i]: %d bytes de %s:%s\n", getpid(), nr_bytes, host, serv);
 
                if (strncmp(buff, "t", strlen(buff)-1) == 0) {
                    time(&secs);
                    nr_bytes = strftime(buff, MAX, "%I:%M:%S %p", localtime(&secs));
                    sendto(sock, buff, nr_bytes, 0, (struct sockaddr *) &addr, addrlen);
                }
                else if (strncmp(buff, "d", strlen(buff)-1) == 0) {
                    time(&secs);
                    nr_bytes = strftime(buff, MAX, "%G-%m-%d", localtime(&secs));
                    sendto(sock, buff, nr_bytes, 0, (struct sockaddr *) &addr, addrlen);
                }
                else if (strncmp(buff, "q", strlen(buff)-1) == 0) {
                    out = 1;
                    printf("Saliendo del proceso [%i]...", getpid());
                    sendto(sock, " ", 1, 0, (struct sockaddr *) &addr, addrlen);
                    close(sock);
                }
                else {
                    printf("Comando no soportado %s", buff);
                    sendto(sock, " ", 1, 0, (struct sockaddr *) &addr, addrlen);
                }
            }
        }
    }
 
    if (pid != 0)
        while ((rpid = wait(&status)) > 0);
 
    close(sockUDP);
 
    return 0;
}
