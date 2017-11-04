/*
 * Client loop back
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define CLIENT_IP	"127.0.0.1"
#define PORT	5000
#define BUFFER_SIZE	100

int main()
{
    struct sockaddr_in client;
    char clientBuffer[BUFFER_SIZE];
    int fd_sock;

    // Create a socket
    fd_sock = socket(AF_INET, SOCK_STREAM, 0);

    //Bind it to a particular IP Address and Port Number
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);
    client.sin_port = htons(PORT);

    connect(fd_sock, (struct sockaddr *)&client, sizeof(client) );

    while(1)
    {
      printf("Enter message: ");
      scanf("%s",clientBuffer);

      write(fd_sock, clientBuffer, BUFFER_SIZE);

      sleep(1);
    }

    return 0;
}
