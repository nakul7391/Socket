/*
 * Socket server
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

#define PORT 5000
#define SERVER_IP	"127.0.0.1"
#define CLIENTS 5
#define BUFFER_SIZE 100

int main()
{
    struct sockaddr_in server;
    int fdclient;
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

    for(i = 0; i < 5; i++)
    {
        printf("Server is waiting\n");
        // Nothing to return from the peer
        // program will wait here for client
        fdclient = accept(fd_sock,NULL,NULL);

        read(fdclient,buffer,BUFFER_SIZE);
        printf("client says: %s\n",buffer);
        close(fdclient);
    }

    close(fd_sock);

    return 0;
}
