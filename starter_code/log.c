//
// Created by David Gu on 9/25/17.
//

#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


int log_file;

void log_init(char *file) {
    if (file == NULL) {
        fprintf(stderr, "can't open output file %s\n", file);
    }
    log_file = open(file, O_RDWR);
}

void log_write(char *fmt, ...) {
    //TODO: remove printf
    printf(fmt);
    char msg[256] = "";
    va_list args;
    va_start(args, fmt);
    vsprintf(msg, fmt, args);
    write(log_file, msg, strlen(msg));
    va_end(args);
}

void log_close() {
    close(log_file);
}