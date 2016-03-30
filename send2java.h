/*
 * send2java - send to java
 *
 * send2java.h
 *
 * Copyright (c) 2016 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef S2J_H
#define S2J_H

#define PROGNAME        "send2java"
#define VERSION         0
#define PATCHLEVEL      0
#define SUBLEVEL        0
#define EXTRAVERSION    ""
#define AUTHOR          "sasairc"
#define MAIL_TO         "sasairc@ssiserver.moe.hm"

#include "./polyaness.h"

typedef struct {
    char*   java;
    char*   jar;
    char*   file;
} s2j_t;

extern int send2java(s2j_t* s2j);
extern int read_s2jrc(s2j_t* s2j, polyaness_t** pt);
extern int write_s2jrc(s2j_t* s2j);
extern int check_file_exists(char* path);
extern char* strlion(int argnum, ...);

/* S2J_H */
#endif
