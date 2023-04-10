# Client-Server-Networking

This repository contains two C files, client.c and server.c, which implement a basic client-server communication using sockets in C language. The client.c file creates a client socket that connects to a server running on the local host, sends a message to the server, and receives a response from the server. The server.c file creates a server socket that listens for incoming connections, accepts a client connection, receives a message from the client, and sends a response back to the client.

## Getting Started

To compile and run these C files, follow the steps below:

1. Clone the repository to your local machine:

    `git clone https://github.com/Rebecca-Rodriguez/Client-Server-Networking.git`

2. Navigate to the repository directory:

    `cd Client-Server-Networking`

3. Compile the `client.c` and `server.c` files using gcc:

    ```
    gcc client.c -o client
    gcc server.c -o server
    ```

4. Run the `server` executable in one terminal window:

    `./server <port>`

    Note: Replace `<port>` with the port number you want the server to listen on.

5. Run the `client` executable in another terminal window:

    `./client <port>`

    Note: Replace `<port>` with the same port number used for the server.

6. Observe the communication between the client and server in the terminal windows.

## Contributing

If you would like to contribute to this project, feel free to fork the repository, make changes, and submit a pull request. Please follow good coding practices and provide detailed commit messages.

## Acknowledgements

This code is based on a basic client-server communication example in C language.
Thanks to the developers of the socket library for providing a powerful tool for network communication in C.
