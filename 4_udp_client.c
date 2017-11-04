#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define CLIENT_IP	"127.0.0.1"
#define CLIENT_PORT	5000
#define CLIENT_BUF	50

int main()
{
	int fdSock, fdClient1, buffer_len;

	struct sockaddr_in clientAddr;

	char clientBuffer[CLIENT_BUF] = "Hi from client";

	//Create a socket
	fdSock = socket(AF_INET, SOCK_DGRAM, 0);

	//Bind it to a particular IP Address and Port Number
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr.s_addr = inet_addr(CLIENT_IP);
	clientAddr.sin_port = htons(CLIENT_PORT);

	//connect(fdSock, (struct sockaddr *)&clientAddr, sizeof(clientAddr) );

  sendto(fdSock,clientBuffer,CLIENT_BUF,0,(struct sockaddr *)&clientAddr, sizeof(clientAddr));
	//Write data into socket
	//write(fdSock, clientBuffer, CLIENT_BUF);

	close(fdSock);
	close(fdClient1);

	return 0;
}
