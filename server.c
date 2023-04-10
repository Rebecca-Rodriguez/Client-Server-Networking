#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const* argv[]) {
	unsigned short port;

	int serverSocket, clientSocket, valRead;
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientLen = sizeof(clientAddr);
	int opt = 1;

	char* message = "Welcome to the server running on REPTILIAN";
	const int BUFFER_SIZE = 256;
	char data[BUFFER_SIZE];

	// Arguments are incorrect
	if (argc < 2 || argc >= 3) {
		perror("Error too many arguments!");
		exit(EXIT_FAILURE);
	}

	// Create a socket file descriptor
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0) {
		perror("Error creating socket!");
		exit(EXIT_FAILURE);
	}

	// Clear address structure
	bzero((char *) &serverAddr, sizeof(serverAddr));

	// Assign port number
	port = atoi(argv[1]);

	// Forcefully attach socket to the port
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		perror("Error with setsockopt!");
		exit(EXIT_FAILURE);
	}

	// Prepare the sockaddr_in structure
	memset(&serverAddr, '\0', sizeof(serverAddr));      // zero structure out
	serverAddr.sin_family = AF_INET;                    // match the socket() call 
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);     // bind to any local address 
	serverAddr.sin_port = htons(port);                  // specify port to listen on

	// Bind the socket to the specified port
	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
		perror("Error binding socket!");
		exit(EXIT_FAILURE);
	}

	// Listen for incoming connections
	if (listen(serverSocket, 3) < 0) {
		perror("Error listening!");
		exit(EXIT_FAILURE);
	}

	// Accept a client connection
	clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
	if (clientSocket < 0) {
		perror("Error accepting connection!");
		exit(EXIT_FAILURE);
	}

	bzero(data, 256);
	valRead = read(clientSocket, data, 255);

	if (valRead < 0) {
		perror("Error reading from socket!");
		exit(EXIT_FAILURE);
	}

	printf("%s\n",data);

	send(clientSocket, message, strlen(message), 0);

	// Close the connected socket
	close(clientSocket);

	// Close the listening socket
	shutdown(serverSocket, SHUT_RDWR);

	return 0;
}