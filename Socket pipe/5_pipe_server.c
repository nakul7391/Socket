/*
  * Server to connet to clients
  *
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
#include <time.h>

#define PORT 5000
#define SERVER_IP	"127.0.0.1"     // Loop back address
#define CLIENTS 2
#define BUFFER_SIZE 100

int main()
{
    struct sockaddr_in server, peer;
    int fdclient[CLIENTS], len;
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
    printf("ctrl+c to quit.........\n");
    // Nothing to return from the peer
    // program will wait here for client

    for(i = 0; i < CLIENTS; i++)
    {
        fdclient[i] = accept(fd_sock,(struct sockaddr *)&peer,&len);
        printf("connected to IP %s PORT %d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
    }

    time_t ttime;
    // read from one client 1 and write to client 2
    while(1)
    {
        ttime = time(NULL);
        read(fdclient[0],buffer,BUFFER_SIZE);
        write(fdclient[1],buffer,BUFFER_SIZE);
        printf("cl1 to cl2: %s@%s",buffer,ctime(&ttime));
        if(strcmp(buffer,"exit") == 0)
        {
            printf("Exiting.....\n");
            break;
        }
    }

    close(fdclient[0]);
    close(fdclient[1]);
    close(fd_sock);

    return 0;
}
