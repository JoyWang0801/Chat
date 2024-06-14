#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <iostream>
#include <time.h>
#include "include/client_connection.h"
// #define MAX 80
// #define PORT 12345
// #define SA struct sockaddr

void chat(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));

		//printf("Enter the string : ");
		printf("Type and hit ENTER to send: ");

		n = 0;
		// while ((buff[n++] = getchar()) != '\n')
        if (fgets(buff, sizeof(buff), stdin) != NULL) {
            // Remove the newline character if present
            size_t len = strlen(buff);
            if (len > 0 && buff[len - 1] == '\n') {
                buff[len - 1] = '\0';
            }
        }

		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}

		// Get current time and print
		time_t mytime = time(NULL);
		char * time_str = ctime(&mytime);
		time_str[strlen(time_str)-1] = '\0';
		printf("%s - %s\n", time_str, buff);

		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));

		read(sockfd, buff, sizeof(buff));
		printf("From Server : %s", buff);
	}
}

void mainLoop()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("10.44.124.21");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
		!= 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	chat(sockfd);

	// close the socket
	close(sockfd);
}
