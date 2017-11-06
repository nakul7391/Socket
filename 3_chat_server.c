/*
 * Socket chat server
 * KILL the process
 * ps -el kill -9
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio_ext.h>

#define PORT 5000
#define SERVER_IP	"127.0.0.1"     // Loop back address
#define CLIENTS 1
#define BUFFER_SIZE 100

int main()
{
    struct sockaddr_in server, peer;
    int fdclient, len;
    char buffer[BUFFER_SIZE];

    // Create a socket
    int fd_sock = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    // Port in network byte order
    server.sin_port = htons(PORT);
    // Convert address to binary and network byte order
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // bind the connection
    bind(fd_sock,(struct sockaddr *)&server,sizeof(server));

    listen(fd_sock,CLIENTS);

    int i;

    printf("Server is up and running\n");
    // Nothing to return from the peer
    // program will wait here for client
    fdclient = accept(fd_sock,(struct sockaddr *)&peer,&len);

    printf("connected to IP %s PORT %d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
    printf("ctrl+c to quit.........\n");
    int opt;
    while(1)
    {
        printf("1.Read 2. Write: ");
        scanf("%d",&opt);
        __fpurge(stdin);
        if(opt == 1)
        {
          read(fdclient,buffer,BUFFER_SIZE);
          printf("server says: %s\n",buffer);
        }
        else if(opt == 2)
        {
          printf("Enter message: ");
          scanf("%[^\n]",buffer);
          write(fdclient, buffer, BUFFER_SIZE);
        }

        __fpurge(stdin);
    }

    close(fd_sock);

    return 0;
}
