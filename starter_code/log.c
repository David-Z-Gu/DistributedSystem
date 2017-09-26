//
// Created by David Gu on 9/25/17.
//

#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

FILE *log_open(const char *path);
void Log(const char *format, ...);

FILE *log_open(const char *path)
{
    FILE *logfile;

    logfile = fopen(path, "w");
    if ( logfile == NULL )
    {
        fprintf(stdout, "Error opening logfile. \n");
        exit(EXIT_FAILURE);
    }

    // set logfile to line buffering
    setvbuf(logfile, NULL, _IOLBF, 0);

    return logfile;
}

void Log(const char *format, ...)
{
    time_t ltime;
    struct tm *Tm;

    ltime = time(NULL);


    va_list ap;
    va_start(ap, format);
    vfprintf(STATE.log, format, ap);
}