//
// Created by David Gu on 9/29/17.
//

#ifndef DISTRIBUTEDSYSTEM_ECHO_SERVER_H
#define DISTRIBUTEDSYSTEM_ECHO_SERVER_H

typedef struct
{
    int  is_secure;
    int  is_static;
    int  content_len;
    char method[MIN_LINE];
    char version[MIN_LINE];
    char uri[MAX_LINE];
    char filename[MAX_LINE];
    char cgiargs[MAX_LINE];
} HTTPContext;

#endif //DISTRIBUTEDSYSTEM_ECHO_SERVER_H
