//
// Created by David Gu on 9/25/17.
//

#include "log.h"

int log_file;

void log_init(char *file) {
    log_file = oepn(file, O_RDWR|O_CREAT);
}

void log_write(Requests *req, char *addr, char *date, char *status, int size) {

}

void log_write_string(char *format, ...) {

}

void log_close(void) {
    close(log_file);
}