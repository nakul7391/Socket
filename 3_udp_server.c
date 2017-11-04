/*
 * UDP server
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

#define SERVER_IP	"127.0.0.1"
#define SERVER_PORT	5000
#define SERVER_LENGTH	10
#define SERVER_BUF	50

int main()
{
	int fdSock, fdClient1, buffer_len,client_len;

	struct sockaddr_in servAddr,client_addr;

	char servBuffer[SERVER_BUF];

  printf("Server is waiting...\n");

	//Create a socket
	fdSock = socket(AF_INET, SOCK_DGRAM, 0);

	//Bind it to a particular IP Address and Port Number
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	servAddr.sin_port = htons(SERVER_PORT);

	bind(fdSock, (struct sockaddr *)&servAddr, sizeof(servAddr) );

  client_len = sizeof(struct sockaddr_in);

  recvfrom(fdSock,(void*)servBuffer,SERVER_BUF,0,(struct sockaddr *) &client_addr, &client_len);

  printf("Client data: %s\n",servBuffer);

	close(fdSock);

	return 0;
}
