//
// Created by David Gu on 9/25/17.
//

#ifndef DISTRIBUTEDSYSTEM_LOG_H
#define DISTRIBUTEDSYSTEM_LOG_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_LINE 200

#define INIT_NEW      1
#define INIT_APPEND   2



void log_init(char *file);
void log_write(Requests *req, char *addr, char *date, char *status, int size);
void log_write_string(char *format, ...);
void log_close(void);

#endif //DISTRIBUTEDSYSTEM_LOG_H

