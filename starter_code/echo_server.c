/******************************************************************************
* echo_server.c                                                               *
*                                                                             *
* Description: This file contains the C source code for an echo server.  The  *
*              server runs on a hard-coded port and simply write back anything*
*              sent to it by connected clients.  It does not support          *
*              concurrent clients.                                            *
*                                                                             *
* Authors: Athula Balachandran <abalacha@cs.cmu.edu>,                         *
*          Wolf Richter <wolf@cs.cmu.edu>                                     *
*                                                                             *
*******************************************************************************/

#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define ECHO_PORT 9999
#define BUF_SIZE 4096

int close_socket(int sock) {
    if (close(sock)) {
        fprintf(stderr, "Failed closing socket.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    fd_set master, read_fds; // master and temp list for select()
    int maxfd, sock, client_sock; //maximum file descriptor #, listening socket descriptor and newly accepted socket descriptor
    int i;
    ssize_t readret; /*ssize_t = the sizes of blocks that can be read or written in a single operation*/
    socklen_t cli_size; /*socklen_t = an integral type of at least 32 bits*/
    struct sockaddr_in addr, cli_addr; /*struct = a user defined data type that allows to combine data items of different kind*/
    //struct addrinfo hints, *serviceinfo, *p;
    char buf[BUF_SIZE];
    int nbytes;

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    fprintf(stdout, "----- Echo Server -----\n");

    /* all networked programs must create a socket */
    /*????????Where is PF_INET defined,SOCK_STREAM defined??????????*/
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) /*socket(int domain, int type, int protocol); call creates an endpoint for communication and return a descriptor*/
    {
        fprintf(stderr, "Failed creating socket.\n");
        return EXIT_FAILURE;
    }
    /*????????Where is addr defined??????????*/
    /*????????Where is AF_INET??????????*/
    addr.sin_family = AF_INET;
    addr.sin_port = htons(ECHO_PORT); /*htons makes sure that the numbers are stored in memory in network bytes order*/
    addr.sin_addr.s_addr = INADDR_ANY; /*????????INADDR_ANY?????*/

    /* servers bind sockets to ports---notify the OS they accept connections */
    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) /*bind(int sockfd, struct sockaddr *my_addr,int addrlen); function assigns a local protocol address to a socket. The protocol address is the combination of either a IPv4 or IPv6 address, along with a 16-bit port number. */
    /*sockfd: a socket descriptor returned by the socket function.
      my_addr − It is a pointer to struct sockaddr that contains the local IP address and port.
      addrlen − Set it to sizeof(struct sockaddr).*/
    {
        close_socket(sock);
        fprintf(stderr, "Failed binding socket.\n");
        return EXIT_FAILURE;
    }


    if (listen(sock, 5) < 0)/*listen(int sockfd,int backlog); converts an unconnected socket into a passive socket, indicating that the kernel should accept incoming connection requests directed to this socket.*/
    /*backlog - the number of allowed connections.*/
    {
        close_socket(sock);
        fprintf(stderr, "Error listening on socket.\n");
        return EXIT_FAILURE;
    }

    FD_SET(sock, &master); // add the current listening descriptor to the monitored set
    maxfd = sock; //initialize maxfd


    /* finally, loop waiting for input and then write it back */
    while (1) {
        read_fds = master;
        if (select(maxfd + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }

        for (i = 0; i <= maxfd; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == sock) {
                    cli_size = sizeof(cli_addr);
                    client_sock = accept(sock, (struct sockaddr *) &cli_addr, &cli_size);
                    /*
                    accept(int socket, struct sockaddr *restrict address,
                    socklen_t *restrict address_len);
                    extrac the first connection on the queue of pending connections,
                    create a new socket with the same socket type protocol
                    */
                    if (client_sock == -1) {
                        perror("accept");
                    } else {
                        FD_SET(client_sock, &master); // add to master set
                        if (client_sock > maxfd) {
                            maxfd = client_sock;
                        }
                        printf("selectserver: new connection from %s on socket %d\n", inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr*)&cli_addr), remoteIP, INET6_ADDRSTRLEN), client_sock);
                    }
                }
                else {
                    readret = 0;
                    // handle data from a client
                    while ((readret = read(i, buf, sizeof buf)) >= 1) {

                        if (send(i, buf, readret, 0) != readret) {
                            close_socket(client_sock);
                            close_socket(sock);
                            fprintf(stderr, "Error sending to client.\n");
                            return EXIT_FAILURE;
                        }
                        memset(buf, 0, BUF_SIZE);
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    }
                    // got error or connection closed by client
                    if (readret == -1) {
                        // connection closed
                        printf("selectserver: socket %d hung up\n", i);
                    }
                }
            }
        }
    }
}
