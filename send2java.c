/*
 * send2java - send to java
 *
 * send2java.c
 *
 * Copyright (c) 2016 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./send2java.h"
#include "./info.h"
#include "./polyaness.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <getopt.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int             res     = 0,
                    index   = 0;

    polyaness_t*    pt      = NULL;

    s2j_t           s2j     = {
        NULL, NULL, NULL};

    struct option   opts[]  = {
        {"java",    required_argument,  NULL,   'j'},
        {"jar",     required_argument,  NULL,   'r'},
        {"file",    required_argument,  NULL,   'f'},
        {"help",    no_argument,        NULL,    0 },
        {"version", no_argument,        NULL,    1 },
        {0, 0, 0, 0},
    };

    if (read_s2jrc(&s2j, &pt) < 0)
        return 1;

    while ((res = getopt_long(argc, argv, "j:r:f:", opts, &index)) != -1) {
        switch (res) {
            case    'j':
                s2j.java = optarg;
                break;
            case    'r':
                s2j.jar = optarg;
                break;
            case    'f':
                s2j.file = optarg;
                break;
            case    0:
                print_usage();
            case    1:
                print_version();
            case    '?':
                return -1;
        }
    }
    if (s2j.file != NULL) {
        if (check_file_exists(s2j.file) < 0)
            return 2;
        s2j.file = realpath(s2j.file, NULL);
    }

    send2java(&s2j);

    if (write_s2jrc(&s2j) < 0)
        return 3;

    if (s2j.file != NULL)
        free(s2j.file);

    release_polyaness(pt);

    return 0;
}

int send2java(s2j_t* s2j)
{
    int status;

    switch (fork()) {
        case    -1:
            fprintf(stderr, "%s: fork() failure\n",
                    PROGNAME);

            return -1;
        case    0:
            execlp(s2j->java, "", "-jar", s2j->jar, s2j->file, NULL);
//          execlp(s2j->java, "", s2j->jar, s2j->file, NULL);

            fprintf(stderr, "%s: %s: not found\n", 
                    PROGNAME, s2j->java);
            exit(errno);
        default:
            waitpid(0, &status, WNOHANG);
    }

    return 0;
}

int read_s2jrc(s2j_t* s2j, polyaness_t** pt)
{
    int     i   = 0;

    char*   rc  = NULL,
        *   val = NULL;
    
    FILE*   fp  = NULL;

    rc = strlion(2, getenv("HOME"), "/.send2javarc");
    if ((fp = fopen(rc, "r")) == NULL)
        return 0;

    init_polyaness(fp, 0, pt);
    if (parse_polyaness(fp, 0, pt) < 0) {
        fprintf(stderr, "%s: parse_polyaness() failure\n",
                PROGNAME);
        fclose(fp);
        free(rc);

        return -1;
    }
    fclose(fp);
    free(rc);

    while (i < (*pt)->recs) {
        if ((val = get_polyaness("java", i, pt)) != NULL)
            s2j->java = val;

        if ((val = get_polyaness("jar", i, pt)) != NULL)
            s2j->jar = val;

        i++;
    }

    return 0;
}

int write_s2jrc(s2j_t* s2j)
{
    char*   rc  = NULL;

    FILE*   fp  = NULL;

    rc = strlion(2, getenv("HOME"), "/.send2javarc");
    if ((fp = fopen(rc, "w")) == NULL) {
        fprintf(stderr, "%s: fopen() failure: %s\n",
                PROGNAME, rc);
        free(rc);

        return -1;
    }
    if (s2j->java != NULL)
        fprintf(fp, "java:%s\n",
                s2j->java);
    if (s2j->jar != NULL)
        fprintf(fp, "jar:%s\n",
                s2j->jar);

    fclose(fp);
    free(rc);

    return 0;
}

int check_file_exists(char* path)
{
    if (access(path, R_OK) < 0) {
        switch (errno) {
            case    EACCES:
                fprintf(stderr, "%s: permission denied: %s\n",
                        PROGNAME, path);
                break;
            case    ENOENT:
                fprintf(stderr, "%s: no such file or directory: %s\n",
                        PROGNAME, path);
                break;
        }

        return -1;
    }

    return 0;
}

char* strlion(int argnum, ...)
{
    int     i       = 0;

    size_t  destlen = 0,
            blklen  = 0,
            arglen  = 0;

    char*   dest    = NULL,
        **  argmnt  = NULL;

    va_list list;       /* list of variable arguments */

    if ((argmnt = (char**)
                malloc(sizeof(char*) * argnum)) == NULL)
        return NULL;

    /* processing of variable arguments */
    va_start(list, argnum);
    while (i < argnum) {
        argmnt[i] = va_arg(list, char*);
        arglen += strlen(argmnt[i]);
        i++;
    }
    va_end(list);

    /* memory allocation */
    if ((dest = (char*)
                malloc(sizeof(char) * (arglen + 1))) == NULL)
        return NULL;

    /* concat strings */
    i = destlen = blklen = 0;

    blklen = strlen(argmnt[i]);
    memcpy(dest, argmnt[i], blklen);
    destlen += blklen;

    i++;
    while(i < argnum) {
        blklen = strlen(argmnt[i]);
        memcpy(dest + destlen, argmnt[i], blklen);
        destlen += blklen;
        i++;
    }
    dest[destlen] = '\0';

    free(argmnt);

    return dest;
}
