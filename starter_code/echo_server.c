/*
 * Echo-based server.
 * Modified from Beej's guide and tutorial on
 * http://forum.codecall.net/topic/64205-concurrent-tcp-server-using-select-api-in-linux-c/
 */

#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>
#include "log.h"
#include "echo_server.h"

#define ECHO_PORT 9999
#define BUF_SIZE 4096

int close_socket(int sock) {
    log_write("closing sock %d\n", sock);
    if (close(sock)) {
        fprintf(stderr, "Failed closing socket.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    fd_set master, read_fds; // master and temp list for select()
    int sock, client_sock; //listening socket descriptor and newly accepted socket descriptor
    int i, j, k;
    int client[FD_SETSIZE], nready;
    int maxfd, max_idx;
    int http_port, www_path;
    char *log_file;
    ssize_t readret; //ssize_t = the sizes of blocks that can be read or written in a single operation
    socklen_t cli_size; //socklen_t = an integral type of at least 32 bits
    struct sockaddr_in addr, cli_addr; //struct = a user defined data type that allows to combine data items of different kind
    char buf[BUF_SIZE];
    int yes = 1;

    //http_port = atoi(argv[1]);
    //www_path = atoi(argv[2]);
    log_file = "test.log";

    /* Get the client address*/
    struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&cli_addr;
    struct in_addr ipAddr = pV4Addr->sin_addr;
    /*Transform the ip address into strings.*/
    //char str[INET_ADDRSTRLEN];
    //inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN ); //Convert IP addresses to human-readable form


    fprintf(stdout, "----- Echo Server -----\n");

    /* all networked programs must create a socket */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) /*socket(int domain, int type, int protocol); call creates an endpoint for communication and return a descriptor*/
    {
        fprintf(stderr, "Failed creating socket.\n");
        return EXIT_FAILURE;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(ECHO_PORT); //htons makes sure that the numbers are stored in memory in network bytes order
    addr.sin_addr.s_addr = INADDR_ANY;

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

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

    for (i=0; i<FD_SETSIZE; i++) {
        client[i] = -1;
    }
    log_init(log_file);
    max_idx = -1;
    maxfd = sock; //initialize maxfd
    FD_ZERO(&master); // initialize descriptor to empty
    FD_SET(sock, &master); // add the current listening descriptor to the monitored set


    /* finally, loop waiting for input and then write it back */
    while (1) {
        read_fds = master;
        nready = select(maxfd + 1, &read_fds, NULL, NULL, NULL);
        if ( nready == -1) {
            perror("select");
            exit(4);
        }

        if (FD_ISSET(sock, &read_fds)) {
            cli_size = sizeof(cli_addr);
            client_sock = accept(sock, (struct sockaddr *) &cli_addr, &cli_size);
            nready--;
            for (j = 0; j <= FD_SETSIZE; j++) {
                if (client[j] < 0) {
                    client[j] = client_sock;

                    FD_SET(client_sock, &master);
                    if (client_sock > maxfd) {
                        maxfd = client_sock;
                    }
                    if (j > max_idx) {
                        max_idx = j;
                    }
                    break;
                }
            }
        }
        else {
            for (k = 0; (k <= max_idx && nready > 0); k++) {
                if (client[k] > 0 && FD_ISSET(client[k], &read_fds)) {
                    nready--;
                    if ((readret = read(client[k], buf, BUF_SIZE)) > 1) {
                        log_write("Server received %d bytes data on %d\n",
                               (int)readret, client[k]);

                        if (send(client[k], buf, readret, 0) != readret) {
                            close_socket(client[k]);
                            close_socket(sock);
                            log_write("Error sending to client.\n");
                            exit(EXIT_FAILURE);
                        }
                        log_write("Server sent %d bytes data to %d\n",
                               (int)readret, client[k]);
                        memset(buf, 0, BUF_SIZE);
                    } else {
                        if (readret == 0) {
                            log_write("serve_clients: socket %d hung up\n", client[k]);
                        }
                        else {
                            log_write("serve_clients: recv return -1\n");
                        }
                        close_socket(client[k]);
                        FD_CLR(client[k], &master);
                        client[k] = -1;
                    }
                }
            }
        }
    }
}



int validate_file(int client_fd, HTTPContext *context, int *is_closed)
{
    struct stat sbuf;

    // check file existence
    if (stat(context->filename, &sbuf) < 0)
    {
        serve_error(client_fd, "404", "Not Found",
                    "Server couldn't find this file", *is_closed);
        return -1;
    }

    // check file permission
    if ((!S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode))
    {
        serve_error(client_fd, "403", "Forbidden",
                    "Server couldn't read this file", *is_closed);
        return -1;
    }

    return 0;
}

void head(int client_fd, HTTPContext *context, int *is_closed)
{
    struct tm tm;
    struct stat sbuf;
    time_t now;
    char   buf[BUF_SIZE], filetype[MIN_LINE], tbuf[MIN_LINE], dbuf[MIN_LINE];

    if (validate_file(client_fd, context, is_closed) < 0) return;

    stat(context->filename, &sbuf);
    get_filetype(context->filename, filetype);

    // get time string
    tm = *gmtime(&sbuf.st_mtime);
    strftime(tbuf, MIN_LINE, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    now = time(0);
    tm = *gmtime(&now);
    strftime(dbuf, MIN_LINE, "%a, %d %b %Y %H:%M:%S %Z", &tm);

    // send response headers to client
    sprintf(buf, "HTTP/1.1 200 OK\r\n");
    sprintf(buf, "%sDate: %s\r\n", buf, dbuf);
    sprintf(buf, "%sServer: Liso/1.0\r\n", buf);
    if (is_closed) sprintf(buf, "%sConnection: close\r\n", buf);
    sprintf(buf, "%sContent-Length: %ld\r\n", buf, sbuf.st_size);
    sprintf(buf, "%sContent-Type: %s\r\n", buf, filetype);
    sprintf(buf, "%sLast-Modified: %s\r\n\r\n", buf, tbuf);
    send(client_fd, buf, strlen(buf), 0);
}