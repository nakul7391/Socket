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
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CLIENT_IP	"127.0.0.1"
#define PORT	5000
#define BUFFER_SIZE	1024

int main(int argc, char *argv[])
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

    int fd = open(argv[1],O_CREAT|O_WRONLY|O_TRUNC);

    if(fd == -1)
    {
        perror("open");
        exit(0);
    }

    int bytes = BUFFER_SIZE;

    while(bytes == BUFFER_SIZE)
    {
      bytes = read(fd_sock, clientBuffer, BUFFER_SIZE);
      write(fd,clientBuffer,bytes);
    }

    close(fd_sock);

    return 0;
}
