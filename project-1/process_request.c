#define BUF_SIZE 4096
#define HTTP_RESPONSE_SIZE 200000
#define MAX_FILE_BUF_SIZE 100000

#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "parse.h"
#include "process_request.h"
#include "log.h"

const char* HTTP_VERSION = "HTTP/1.1 ";
const char* STATUS_200 = "200 OK\r\n";
const char* STATUS_204 = "204 NO CONTENT\r\n";
const char* STATUS_400 = "400 BAD REQUEST\r\n";
const char* STATUS_404 = "404 NOT FOUND\r\n";
const char* STATUS_405 = "405 METHOD NOT ALLOWED\r\n";
const char* STATUS_411 = "411 Length REQUIRED\r\n";
const char* STATUS_415 = "415 UNSUPPORTED MEDIA TYPE\r\n";
const char* STATUS_500 = "500 INTERNAL SERVER ERROR\r\n";
const char* STATUS_501 = "501 NOT IMPLEMENTED\r\n";
const char* STATUS_505 = "505 HTTP VERSION NOT SUPPORTED\r\n";

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

void process_head(Request * request, char * response, char * resource_path){
    char file_path[BUF_SIZE], content_type[BUF_SIZE];
    size_t content_length;

    fprintf(stdout, "req uri %s\n", request->http_uri);
    // get request uri to get location of file
    strcat(file_path, resource_path);
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
    //modified time and dates
    write_to_log(request, response);

    sprintf(response, "%sServer: Liso/1.0\r\n", response);
    /*
    if (is_closed) {
        sprintf(buf, "%sConnection: close\r\n", response);
    }
    else{
        sprintf(buf, "%sConnection: is alive\r\n", response);
    }
     */
    sprintf(response, "%sContent-Length: %ld\r\n", response, content_length);
    sprintf(response, "%sContent-Type: %s\r\n", response, content_type);
    //sprintf(buf, "%sLast-Modified: %s\r\n\r\n", buf, tbuf);
    strcat(response, "\r\n");

    memset(file_path, 0, BUF_SIZE);
    memset(nbytes, 0, MAX_FILE_BUF_SIZE);
    memset(content_type, 0, BUF_SIZE);
}

void process_get(Request * request, char * response, char * resource_path){
    char file_path[BUF_SIZE], content_type[BUF_SIZE];
    size_t content_length;

    fprintf(stdout, "req uri %s\n", request->http_uri);
    // get request uri to get location of file
    strcat(file_path, resource_path);
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
    //modified time and dates
    write_to_log(request, response);

    sprintf(response, "%sServer: Liso/1.0\r\n", response);
    /*
    if (is_closed) {
        sprintf(buf, "%sConnection: close\r\n", response);
    }
    else{
        sprintf(buf, "%sConnection: is alive\r\n", response);
    }
     */
    sprintf(response, "%sContent-Length: %ld\r\n", response, content_length);
    sprintf(response, "%sContent-Type: %s\r\n", response, content_type);
    //sprintf(buf, "%sLast-Modified: %s\r\n\r\n", buf, tbuf);
    strcat(response, "\r\n");

    strcat(response, nbytes);

    memset(file_path, 0, BUF_SIZE);
    memset(nbytes, 0, MAX_FILE_BUF_SIZE);
    memset(content_type, 0, BUF_SIZE);
}

void process_post(Request * request, char * response, char * resource_path){
    char file_path[BUF_SIZE];

    fprintf(stdout, "req uri %s\n", request->http_uri);
    // get request uri to get location of file
    strcat(file_path, resource_path);
    strcat(file_path, request->http_uri);

    int file = check_file_access(file_path, response);
    if (file < 0) {
        return;
    }

    char * content_length;
    // get content-length from header
    for (int i=0; i< request->header_count; i++){
        if (strcmp(request->headers[i].header_name, "Content-Length") || strcmp(request->headers[i].header_name, "content-length")){
            content_length = request->headers[i].header_value;
        }
    }

    if (content_length == NULL) {
        // return 411
        strcat(response, HTTP_VERSION);
        strcat(response, STATUS_411);
        strcat(response, "\r\n");
        return;
    }

    // process body of post??

    //modified time and dates
    write_to_log(request, response);

    printf("successful post");
    strcat(response, HTTP_VERSION);
    strcat(response, STATUS_200);
    sprintf(response, "%sServer: Liso/1.0\r\n", response);
    sprintf(response, "%sContent-Length: %s\r\n", response, content_length);
    strcat(response, "\r\n");

    memset(file_path, 0, BUF_SIZE);
}

void process_http_request(Request * request, char * response, char * resource_path) {
    if (request == NULL) {
        log_write("Bad Request. Request cannot be parsed!\n");
        strcat(response, HTTP_VERSION);
        strcat(response, STATUS_400);
        strcat(response, "\r\n");
        return;
    }

    if (!strcmp(request->http_version, HTTP_VERSION)) {
        log_write("HTTP Version %s not supported.\n", request->http_version);
        strcat(response, HTTP_VERSION);
        strcat(response, STATUS_505);
        strcat(response, "\r\n");
        return;
    }

    if (strcmp(request->http_method, "HEAD") == 0) {
        log_write("Processing a HEAD request");
        process_head(request, response, resource_path);
    }
    else if (strcmp(request->http_method, "GET") == 0) {
        log_write("Processing a GET request");
        process_get(request, response, resource_path);
    }
    else if (strcmp(request->http_method, "POST") == 0) {
        log_write("Processing a POST request");
        process_post(request, response, resource_path);
    }
    else {
        log_write("Requested http method %s is not implemented.",  request->http_method);
        strcat(response, HTTP_VERSION);
        strcat(response, STATUS_501);
        strcat(response, "\r\n");
    }
}

void write_to_log(Request * request, char * response){
    struct tm tm;
    struct stat sbuf;
    time_t now;
    char filetype[100], tbuf[100], dbuf[100];
    stat(request->http_uri, &sbuf);
    tm = *gmtime(&sbuf.st_mtime); //st_mtime: time of last data modification.
    //printf("yeah %d", mktime(tm));
    /*
    if (&tm == 2){
        now = time(0);
        tm = *gmtime(&now);
    }
     */
    /*
    if (b->stage == STAGE_CLOSE)
        sprintf(response, "%sConnection: Close\r\n", response);
    else
        sprintf(response, "%sConnection: Keep-Alive\r\n", response);
    */
    strftime(tbuf, 1000, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    sprintf(response, "%sLast-Modified: %s\r\n", response, tbuf);

    now = time(0);
    tm = *gmtime(&now);
    strftime(dbuf, 100, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    sprintf(response, "%sDate: %s\r\n", response, dbuf);
}



void check_clients(int * max_idx, int * nready, int * client, fd_set* read_fds)
{
    int i, connfd, is_closed;

    for (i=0; (i <= max_idx) && (nready > 0); i++)
    {
        connfd = client[i];

        if ((connfd > 0) && (FD_ISSET(connfd, read_fds)))
        {
            nready--;
            is_closed = 0;
            if (is_closed)
                printf("Connection: Close\r\n");
            else
                printf("Connection: Keep-Alive\r\n");
            //process_http_request(i, p, &is_closed);
            //if (is_closed) remove_client(i, p);
        }
    }
}
