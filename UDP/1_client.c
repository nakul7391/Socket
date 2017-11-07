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
#define SIZE	50

int main()
{
	int fdSock, buffer_len,len;

	struct sockaddr_in client;

	char data[SIZE] = "Hi from client";

	//Create a socket
	fdSock = socket(AF_INET, SOCK_DGRAM, 0);

	//Bind it to a particular IP Address and Port Number
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = inet_addr(CLIENT_IP);
	client.sin_port = htons(CLIENT_PORT);

  sendto(fdSock,data,SIZE,0,(struct sockaddr *)&client, sizeof(client));

  recvfrom(fdSock,data,SIZE,0,NULL,NULL);

  printf("%s\n",data);

	close(fdSock);

	return 0;
}
