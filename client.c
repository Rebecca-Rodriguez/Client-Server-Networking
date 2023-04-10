#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	unsigned short port;

	int clientSocket, valRead;
	struct sockaddr_in clientAddr;

	char* message = "Rebecca Velez: 9939-6591";
	const int BUFFER_SIZE = 256;
	char data[BUFFER_SIZE];

	// Arguments are incorrect
	if (argc < 2 || argc >= 3) {
		perror("ERROR: Too many arguments");
		exit(EXIT_FAILURE);
	}

	// Create a socket file descriptor
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0) {
		perror("Error creating socket!");
		exit(EXIT_FAILURE);
	}

	// Clear address structure
	bzero((char *) &clientAddr, sizeof(clientAddr));

	// Assign port number
	port = atoi(argv[1]);

	// Prepare the sockaddr_in structure
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &clientAddr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(clientSocket, (struct sockaddr *) &clientAddr, sizeof(clientAddr)) < 0) {
		perror("ERROR connecting");
		exit(EXIT_FAILURE);
	}

	send(clientSocket, message, strlen(message), 0);
	bzero(data, 256);
	valRead = read(clientSocket, data, 255);

	if (valRead < 0) {
		perror("ERROR reading from socket");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", data);

	// Close the connected socket
	close(clientSocket);

	return 0;
}