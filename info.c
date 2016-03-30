/*
 * send2java - send to java
 *
 * info.c
 *
 * Copyright (c) 2016 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./send2java.h"
#include "./info.h"
#include <stdio.h>
#include <stdlib.h>

int print_version(void)
{
    fprintf(stdout, "%s %d.%d.%d%s (%s)\n",
            PROGNAME, VERSION, PATCHLEVEL, SUBLEVEL, EXTRAVERSION, ARCH);

    exit(0);
}

int print_usage(void)
{
    fprintf(stdout, "\
%s %d.%d.%d%s, send to java.\n\
Usage: send2java [OPTION]...\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\n\
  -j,  --java=JAVA           specifies java execution environment\n\
  -r,  --jar=JAR             specifies jar content\n\
  -f   --file=FILE           manually specifies file\n\
\n\
       --help                display this help and exit\n\
       --version             optput version infomation and exit\n\
\n\
Report %s bugs to %s <%s>\n\
",
        PROGNAME, VERSION, PATCHLEVEL, SUBLEVEL, EXTRAVERSION,
        PROGNAME, AUTHOR, MAIL_TO);

    exit(0);
}
