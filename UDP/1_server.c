#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>

#define SERVER_IP	"127.0.0.1"
#define SERVER_PORT	5000
#define SIZE	50

int main()
{
	int fdSock,buffer_len,len;

	struct sockaddr_in server,client;

	char data[SIZE];

  printf("Server is waiting...\n");

	//Create a socket
	fdSock = socket(AF_INET, SOCK_DGRAM, 0);

	//Bind it to a particular IP Address and Port Number
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_port = htons(SERVER_PORT);

	bind(fdSock, (struct sockaddr *)&server, sizeof(server) );


  len = sizeof(struct sockaddr_in);

  // get client address here
  recvfrom(fdSock,data,SIZE,0,(struct sockaddr *)&client, &len);

  printf("Client data: %s\n",data);

  strcpy(data,"hello");

  sendto(fdSock,data,SIZE,0,(struct sockaddr *)&client,len);

	close(fdSock);

	return 0;
}
