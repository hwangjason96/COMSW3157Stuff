
/* Author: Claude, Jae Sung Hwang
 * Skeleton provided by Claude, finished by Jae Sung.
 *
 * tcp_server.c - Echo Server Skeleton
 *
 * Usage: ./tcp_server <port>
 * Example: ./tcp_server 8080
 *
 * This server accepts ONE client, echoes back whatever it receives, then exits.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

#define MAXPENDING 5
#define BUFSIZE    256
 
int main(int argc, char *argv[]) {
 
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }
 
    /* -------------------------------------------------------
     * STEP 1: Create a TCP socket
     *
     * TODO: Call socket() with the right domain, type, protocol.
     *       Store the result in `serversock`.
     *       On error, print a message and exit.
     *
     * Hint: domain = AF_INET, type = SOCK_STREAM, protocol = 0
     * ------------------------------------------------------- */
    int serversock;
 
    /* YOUR CODE HERE */
    //This returns a file descriptor, which I know from dup2, but I
    //think I need a little more brushing up on that concept.
    serversock = socket(AF_INET, SOCK_STREAM, 0);
    //The first parameter is the IP Address that will be associated with
    //the second parameter of the connection type (for us TCP-IP)
    //The third parameter is the protocol (apparently 0 is "obvious",
    //needs a little more digging).
 
    /* -------------------------------------------------------
     * STEP 2: Fill in the server address struct
     *
     * TODO: Zero out `echoserver`, then set:
     *   - sin_family  = AF_INET
     *   - sin_addr    = INADDR_ANY  (accept on all interfaces)
     *   - sin_port    = the port from argv[1]
     *
     * Hint: use htonl() for the address and htons() for the port.
     *       atoi(argv[1]) converts the string argument to an int.
     * ------------------------------------------------------- */
    struct sockaddr_in echoserver;
 
    /* YOUR CODE HERE */
    //Set everything to 0
    memset(&echoserver, 0, sizeof(echoserver));
    //set up the IP Address for the server
    //This cannot differ from the socket you are going to
    //associate to when calling bind(). OS will error
    echoserver.sin_family = AF_INET;
    //little to big endian
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY);
    //big to little endian
    echoserver.sin_port = htons(atoi(argv[1]));
 
    /* -------------------------------------------------------
     * STEP 3: Bind the socket to the address
     *
     * TODO: Call bind().
     *       On error, print a message and exit.
     *
     * Hint: cast &echoserver to (struct sockaddr *)
     * ------------------------------------------------------- */
 
    /* YOUR CODE HERE */
    //Bind does a couple of things:
    //1. It binds the assigned server type to the echoserver struct
    //2. It assigns the IP-address to the port and associates it as
    //the known ip address and port to connect to
    if (bind(serversock, (struct sockaddr *) &echoserver, sizeof(echoserver)) < 0) {
	    fprintf(stderr,"Error: bind failed %s.\n", strerror(errno));
	    return EXIT_FAILURE;
    }
 
    /* -------------------------------------------------------
     * STEP 4: Start listening for incoming connections
     *
     * TODO: Call listen() with MAXPENDING as the backlog.
     *       On error, print a message and exit.
     * ------------------------------------------------------- */
 
    /* YOUR CODE HERE */
    //Listen essentially opens up a protocol that watches for a
    //specific pattern in the TCP/IP stack.
    //It takes the file descriptor at the first parameter and 
    //takes its state to LISTENING.
    if(listen(serversock, MAXPENDING) < 0) {
	    fprintf(stderr,"Error listen failed %s.\n", strerror(errno));
	    return EXIT_FAILURE;
    }
    //Treat it almost like a class method, where the first argument
    //is the member variable you are working with.

    printf("Server listening on port %s...\n", argv[1]);
 
    /* -------------------------------------------------------
     * STEP 5: Accept one incoming client connection
     *
     * TODO: Declare a `struct sockaddr_in echoclient` and a
     *       `socklen_t clientlen = sizeof(echoclient)`.
     *       Call accept() and store the result in `clientsock`.
     *       On error, print a message and exit.
     *
     * Note: accept() BLOCKS here until a client connects.
     * ------------------------------------------------------- */
    int clientsock;
    struct sockaddr_in echoclient;
    socklen_t clientlen = sizeof(echoclient);
 
    /* YOUR CODE HERE */
    // takes the next pending connection off the queue,
    // and returns a new socket file descriptor for that client

    //Notice the clientlen, it is there because it knows how big the struct
    //is going in, and changes by how many bytes it actually gets filled in
    //from the connection that is established.
    //It is for size safety
    clientsock = accept(serversock, (struct sockaddr *) &echoclient, &clientlen);
    //even after this is finished, listen() is still on and it will continue
    //listening for connections on serversock.

    //echo client is now:
    //echoclient.sin_family       // AF_INET
    //echoclient.sin_addr.s_addr  // the CLIENT's IP address
    //echoclient.sin_port         // the CLIENT's ephemeral port
    
    printf("Client connected: %s\n", inet_ntoa(echoclient.sin_addr));
 
    /* -------------------------------------------------------
     * STEP 6: Receive data from the client
     *
     * TODO: Declare `char buffer[BUFSIZE]` and call recv().
     *       Store bytes received in `num_recv`.
     *       Handle error (num_recv < 0) and EOF (num_recv == 0).
     * ------------------------------------------------------- */
    char buffer[BUFSIZE];
    ssize_t num_recv;
 
    /* YOUR CODE HERE */
    //recv accesses the buffer sitting in the kernel and copies it
    //to the buffer in the parameter.
    num_recv = recv(clientsock, buffer, BUFSIZE, 0);
    //Interesting thing about this is that the message is automatically
    //handled by the TCP/IP Stack, and the information is saved and
    //ready for access.
    if (num_recv < 0) {
	fprintf(stderr, "recv failed: %s\n", strerror(errno));
	return EXIT_FAILURE;
    }
    if (num_recv == 0) {
	printf("Client disconnected\n");
	close(clientsock);
	close(serversock);
	return EXIT_SUCCESS;
    }
    buffer[num_recv] = '\0';
    //There is a cap to this number, and the sender will slow down based
    //on how much of this cap is used. TCP will constantly listen for
    //messages as long as the socket is opened.

    //No way of organizing between the different messages being sent
    //from the client. Organizing is entirely based on the agreement
    //between the client and the server. So buffering is up to me.

    printf("Received %zd bytes: %s\n", num_recv, buffer);
 
    /* -------------------------------------------------------
     * STEP 7: Echo the data back to the client
     *
     * TODO: Call send() to send `buffer` back.
     *       Send exactly `num_recv` bytes.
     * ------------------------------------------------------- */
 
    /* YOUR CODE HERE */
    send(clientsock, buffer, num_recv, 0);
    printf("Echoed data back to client.\n");
 
    /* -------------------------------------------------------
     * STEP 8: Close both sockets
     *
     * TODO: close(clientsock) and close(serversock).
     * ------------------------------------------------------- */
 
    /* YOUR CODE HERE */
    close(clientsock);
    close(serversock);
    return 0;
}

