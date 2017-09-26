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

int close_socket(int sock)
{
    if (close(sock))
    {
        fprintf(stderr, "Failed closing socket.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    int sock, client_sock;
    ssize_t readret; /*ssize_t = the sizes of blocks that can be read or written in a single operation*/
    socklen_t cli_size; /*socklen_t = an integral type of at least 32 bits*/
    struct sockaddr_in addr, cli_addr; /*struct = a user defined data type that allows to combine data items of different kind*/
    char buf[BUF_SIZE];

    fprintf(stdout, "----- Echo Server -----\n");

    /* all networked programs must create a socket */
    /*????????Where is PF_INET defined,SOCK_STREAM defined??????????*/
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) /*socket(int domain, int type, int protocol); call creates an endpoint for communication and return a descriptor*/
    {
        fprintf(stderr, "Failed creating socket.\n");
        return EXIT_FAILURE;
    }
    /*????????Where is AF_INET??????????*/
    addr.sin_family = AF_INET;
    addr.sin_port = htons(ECHO_PORT); /*htons makes sure that the numbers are stored in memory in network bytes order*/
    addr.sin_addr.s_addr = INADDR_ANY; /*????????INADDR_ANY?????*/

    /* servers bind sockets to ports---notify the OS they accept connections */
    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr))) /*bind(int sockfd, struct sockaddr *my_addr,int addrlen); function assigns a local protocol address to a socket. The protocol address is the combination of either a IPv4 or IPv6 address, along with a 16-bit port number. */
    /*sockfd: a socket descriptor returned by the socket function.
      my_addr − It is a pointer to struct sockaddr that contains the local IP address and port.
      addrlen − Set it to sizeof(struct sockaddr).*/
    {
        close_socket(sock);
        fprintf(stderr, "Failed binding socket.\n");
        return EXIT_FAILURE;
    }


    if (listen(sock, 5))/*listen(int sockfd,int backlog); converts an unconnected socket into a passive socket, indicating that the kernel should accept incoming connection requests directed to this socket.*/
    /*backlog - the number of allowed connections.*/
    {
        close_socket(sock);
        fprintf(stderr, "Error listening on socket.\n");
        return EXIT_FAILURE;
    }

    /* finally, loop waiting for input and then write it back */
    while (1)
    {
       cli_size = sizeof(cli_addr);
       if ((client_sock = accept(sock, (struct sockaddr *) &cli_addr,
                                 &cli_size)) == -1)
      /*
      accept(int socket, struct sockaddr *restrict address,
      socklen_t *restrict address_len);
      extrac the first connection on the queue of pending connections,
      create a new socket with the same socket type protocol
      */
       {
           close(sock);
           fprintf(stderr, "Error accepting connection.\n");
           return EXIT_FAILURE;
       }

       readret = 0;

       while((readret = recv(client_sock, buf, BUF_SIZE, 0)) >= 1)
       /*
       recv(int s, void *buf, size_t len, int flags);
       read incoming data from the remote side
       */
       {
           if (send(client_sock, buf, readret, 0) != readret)
           /*
           ssize_t send(int socket, const void *buffer, size_t length, int flags);
           initiate transmission of a message from the specified socket to its peer
           */
           {
               close_socket(client_sock);
               close_socket(sock);
               fprintf(stderr, "Error sending to client.\n");
               return EXIT_FAILURE;
           }
           memset(buf, 0, BUF_SIZE);
           /*
           memset(void *str, int c, size_t n);
           str -- This is a pointer to the block of memory to fill.
           c -- This is the value to be set. The value is passed as an int, but the function fills the block of memory using the unsigned char conversion of this value.
           n -- This is the number of bytes to be set to the value.

           copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str.
           */
       }

       if (readret == -1)
       {
           close_socket(client_sock);
           close_socket(sock);
           fprintf(stderr, "Error reading from client socket.\n");
           return EXIT_FAILURE;
       }

       if (close_socket(client_sock))
       {
           close_socket(sock);
           fprintf(stderr, "Error closing client socket.\n");
           return EXIT_FAILURE;
       }
    }

    close_socket(sock);

    return EXIT_SUCCESS;
}
