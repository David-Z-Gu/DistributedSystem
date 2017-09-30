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
#include <fcntl.h>
#include "log.h"
#include "parse.h"

#define ECHO_PORT 9999
#define BUF_SIZE 4096
#define HTTP_RESPONSE_SIZE 200000
#define MAX_FILE_BUF_SIZE 100000

char* HTTP_VERSION = "HTTP/1.1 ";
char* STATUS_200 = "200 OK\r\n";
char* STATUS_204 = "204 NO CONTENT\r\n";
char* STATUS_404 = "404 NOT FOUND\r\n";
char* STATUS_405 = "405 METHOD NOT ALLOWED\r\n";
char* STATUS_415 = "415 UNSUPPORTED MEDIA TYPE\r\n";
char* STATUS_500 = "500 INTERNAL SERVER ERROR\r\n";
char* STATUS_501 = "501 NOT IMPLEMENTED\r\n";
char* STATUS_505 = "505 HTTP VERSION NOT SUPPORTED\r\n";

int close_socket(int sock) {
    log_write("closing sock %d\n", sock);
    if (close(sock)) {
        fprintf(stderr, "Failed closing socket.\n");
        return 1;
    }
    return 0;
}

void get_content_type(char *file_ext, char *content_type) {
    if (strstr(file_ext, ".html")) {
        strcpy(content_type, "text/html");
    }
    else if (strstr(file_ext, ".css")) {
        strcpy(content_type, "text/css");
    }
    else if (strstr(file_ext, ".png")) {
        strcpy(content_type, "image/png");
    }
    else if (strstr(file_ext, ".jpeg")) {
        strcpy(content_type, "image/jpeg");
    }
    else if (strstr(file_ext, ".gif")) {
        strcpy(content_type, "image/gif");
    }
    else {
        strcpy(content_type, "application/octet-stream");
    }
}

int check_file_access(char *file_path, char *response) {
    if (access(file_path, F_OK) == -1) {
        log_write("cannot access file at %s\n", file_path);
        // return not found
        strcat(response, HTTP_VERSION);
        strcat(response, STATUS_404);
        strcat(response, "\r\n");
    }
    // open uri w readyonly
    int file = open(file_path, O_RDONLY);
    if (file == -1) {
        log_write("can't open file at %s\n", file_path);
        strcat(response, HTTP_VERSION);
        strcat(response, STATUS_500);
        strcat(response, "\r\n");
    }
    return file;
}

void process_head(Request * request, char * response){
    char file_path[BUF_SIZE], content_type[BUF_SIZE];
    size_t content_length;

    fprintf(stdout, "req uri %s\n", request->http_uri);
    // get request uri to get location of file
    strcat(file_path, "www");
    strcat(file_path, request->http_uri);

    int file = check_file_access(file_path, response);
    if (file < 0) {
        return;
    }

    char nbytes[MAX_FILE_BUF_SIZE];
    // get content length from reading file
    content_length = read(file, nbytes, sizeof(nbytes));

    // get content type based on uri
    get_content_type(request->http_uri, content_type);

    // construct response
    //sprintf(response, "HTTP/1.1 200 OK\r\n");
    strcat(response, HTTP_VERSION);
    strcat(response, STATUS_200);
    //sprintf(response, "%sDate: %s\r\n", response, dbuf);
    sprintf(response, "%sServer: Liso/1.0\r\n", response);
    //if (is_closed) sprintf(buf, "%sConnection: close\r\n", response);
    sprintf(response, "%sContent-Length: %ld\r\n", response, content_length);
    sprintf(response, "%sContent-Type: %s\r\n", response, content_type);
    //sprintf(buf, "%sLast-Modified: %s\r\n\r\n", buf, tbuf);
    strcat(response, "\r\n");

    memset(file_path, 0, BUF_SIZE);
    memset(nbytes, 0, MAX_FILE_BUF_SIZE);
    memset(content_type, 0, BUF_SIZE);
}

void process_get(Request * request, char * response){
    char file_path[BUF_SIZE], content_type[BUF_SIZE];
    size_t content_length;

    fprintf(stdout, "req uri %s\n", request->http_uri);
    // get request uri to get location of file
    strcat(file_path, "www");
    strcat(file_path, request->http_uri);

    int file = check_file_access(file_path, response);
    if (file < 0) {
        return;
    }

    char nbytes[MAX_FILE_BUF_SIZE];
    // get content length from reading file
    content_length = read(file, nbytes, sizeof(nbytes));

    // get content type based on uri
    get_content_type(request->http_uri, content_type);

    // construct response
    strcat(response, HTTP_VERSION);
    strcat(response, STATUS_200);
    //sprintf(response, "%sDate: %s\r\n", response, dbuf);
    sprintf(response, "%sServer: Liso/1.0\r\n", response);
    //if (is_closed) sprintf(buf, "%sConnection: close\r\n", response);
    sprintf(response, "%sContent-Length: %ld\r\n", response, content_length);
    sprintf(response, "%sContent-Type: %s\r\n", response, content_type);
    //sprintf(buf, "%sLast-Modified: %s\r\n\r\n", buf, tbuf);
    strcat(response, "\r\n");

    strcat(response, nbytes);

    memset(file_path, 0, BUF_SIZE);
    memset(nbytes, 0, MAX_FILE_BUF_SIZE);
    memset(content_type, 0, BUF_SIZE);
}

void process_post(Request * request, char * response){
    //TODO need to update file for post
    if (access(request->http_uri, F_OK ) == -1) {
        log_write("%s cannot be accessed", request->http_uri);
        strcat(response, HTTP_VERSION);
        strcat(response, STATUS_204);
        strcat(response, "\r\n");
    }
    else {
        //TODO: more in response headers?
        printf("successful post");
        strcat(response, HTTP_VERSION);
        strcat(response, STATUS_200);
        sprintf(response, "%sServer: Liso/1.0\r\n", response);
        strcat(response, "\r\n");
    }
}

int main(int argc, char *argv[]) {
    fd_set master, read_fds; // master and temp list for select()
    int sock, client_sock; //listening socket descriptor and newly accepted socket descriptor
    int i, j, k;
    int client[FD_SETSIZE], nready;
    int maxfd, max_idx;
    int http_port;
    char *www_path, *log_file;
    ssize_t readret; /*ssize_t = the sizes of blocks that can be read or written in a single operation*/
    socklen_t cli_size; /*socklen_t = an integral type of at least 32 bits*/
    struct sockaddr_in addr, cli_addr; /*struct = a user defined data type that allows to combine data items of different kind*/
    char buf[BUF_SIZE];
    int yes = 1;

    //http_port = atoi(argv[1]);
    //www_path = atoi(argv[2]);
    www_path = "www/";
    log_file = "test.log";

    fprintf(stdout, "----- Lisod Server -----\n");

    /* all networked programs must create a socket */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) /*socket(int domain, int type, int protocol); call creates an endpoint for communication and return a descriptor*/
    {
        fprintf(stderr, "Failed creating socket.\n");
        return EXIT_FAILURE;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(ECHO_PORT); /*htons makes sure that the numbers are stored in memory in network bytes order*/
    addr.sin_addr.s_addr = INADDR_ANY;

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    /* servers bind sockets to ports---notify the OS they accept connections */
    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        close_socket(sock);
        fprintf(stderr, "Failed binding socket.\n");
        return EXIT_FAILURE;
    }


    if (listen(sock, 5) < 0)
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

                        // handle request
                        Request *request = parse(buf, readret, client[k]);
                        char * response = malloc(20000);

                        if (request == NULL) {
                            log_write("Bad Request. Request cannot be parsed!");
                            //TODO: response with 400?
                            break;
                        }
//                        printf("http method %s\n", request->http_method);
//                        printf("http version %s\n", request->http_version);
//                        printf("http uri %s\n", request->http_uri);
                        for (i=0; i< request->header_count; i++){
                            printf("header name %s header value %s\n", request->headers[i].header_name, request->headers[i].header_value);
                        }

                        if (strcmp(request->http_method, "HEAD") == 0) {
                            fprintf(stdout, "encountered a HEAD request\n");
                            process_head(request, response);
                        }
                        else if (strcmp(request->http_method, "GET") == 0) {
                            fprintf(stdout, "encountered a GET request\n");
                            process_get(request, response);
                        }
                        else if (strcmp(request->http_method, "POST") == 0) {
                            fprintf(stdout, "encountered a POST request\n");
                            process_post(request, response);
                        }
                        else {
                            fprintf(stdout, "Response with 501");
                        }
                        printf("response size is %lu\n", strlen(response));
                        printf("response is %s\n", response);
                        if (send(client[k], response, strlen(response), 0) < 0) {
                            close_socket(client[k]);
                            close_socket(sock);
                            log_write("Error sending to client.\n");
                            exit(EXIT_FAILURE);
                        }
                        log_write("Server sent %d bytes data to %d\n",
                               strlen(response), client[k]);
                        free(response);
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
