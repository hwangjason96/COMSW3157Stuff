/*
 * tcp_client.c - Echo Client Skeleton
 *
 * Usage: ./tcp_client <server_ip> <port> <message>
 * Example: ./tcp_client 127.0.0.1 8080 "hello world"
 *
 * This client connects to the echo server, sends a message,
 * receives the echo back, prints it, and exits.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

#define BUFSIZE 256

int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <server_ip> <port> <message>\n", argv[0]);
        exit(1);
    }

    /* -------------------------------------------------------
     * STEP 1: Create a TCP socket
     *
     * TODO: Same as the server — call socket() and store the
     *       result in `clientsock`. Check for errors.
     * ------------------------------------------------------- */
    int clientsock;

    /* YOUR CODE HERE */
    clientsock = socket(AF_INET,SOCK_STREAM,0);
    /* -------------------------------------------------------
     * STEP 2: Fill in the server address struct
     *
     * TODO: Zero out `echoserver`, then set:
     *   - sin_family  = AF_INET
     *   - sin_addr    = the IP address from argv[1]
     *   - sin_port    = the port from argv[2]
     *
     * Hint: use inet_addr(argv[1]) for the IP address.
     *       (Unlike the server which used INADDR_ANY, the client
     *        needs the actual server IP to connect to.)
     * ------------------------------------------------------- */
    struct sockaddr_in echoserver;
    /* YOUR CODE HERE */
    echoserver.sin_family = AF_INET;
    echoserver.sin_addr.s_addr = inet_addr(argv[1]);
    echoserver.sin_port = htons(atoi(argv[2]));


    /* -------------------------------------------------------
     * STEP 3: Connect to the server
     *
     * TODO: Call connect().
     *       On error, print a message and exit.
     *
     * Note: The client does NOT call bind() or listen().
     *       The OS automatically assigns an ephemeral port.
     * ------------------------------------------------------- */

    /* YOUR CODE HERE */
    if (connect(clientsock, (struct sockaddr *) &echoserver, sizeof(echoserver)) <0) {
	    fprintf(stderr,"Error: connect failed. %s\n",strerror(errno));
	    return EXIT_FAILURE;
    }
    printf("Connected to server %s:%s\n", argv[1], argv[2]);

    /* -------------------------------------------------------
     * STEP 4: Send the message to the server
     *
     * TODO: Use send() to send argv[3].
     *       Send strlen(argv[3]) + 1 bytes (include the '\0').
     * ------------------------------------------------------- */

    /* YOUR CODE HERE */
    if (send(clientsock, argv[3], strlen(argv[3]) + 1, 0) < 0) {
	    fprintf(stderr,"Error: send failed. %s\n",strerror(errno));
	    return EXIT_FAILURE;
    }
    printf("Sent: %s\n", argv[3]);

    /* -------------------------------------------------------
     * STEP 5: Receive the echoed response
     *
     * TODO: Declare `char buffer[BUFSIZE]` and call recv().
     *       Print the received message.
     * ------------------------------------------------------- */
    char buffer[BUFSIZE];

    /* YOUR CODE HERE */
    size_t num_rec;
    if( (num_rec = recv(clientsock,buffer,BUFSIZE,0) ) < 0) {
	    fprintf(stderr,"Error: recv failed. %s\n",strerror(errno));
	    return EXIT_FAILURE;
    }
    printf("Received: %s. Byte size: %zd\n",buffer, num_rec);
    /* -------------------------------------------------------
     * STEP 6: Close the socket
     *
     * TODO: close(clientsock).
     * ------------------------------------------------------- */

    /* YOUR CODE HERE */
    close(clientsock);
    return 0;
}
