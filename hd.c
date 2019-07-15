#include "config.h"
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <fcntl.h>
/* #include <stdlib.h> */
#include <stdio.h>
#ifndef O_BINARY
#define O_BINARY 0
#endif
#include "hexdump.h"

int main(int argc, char *argv[])
{
    int fd, n;
    unsigned long ofs;
    static unsigned char buf[128];
/*
    extern unsigned char ii[];
    extern int sizeof_ii;
    
    hexdump(ii, sizeof_ii, 0);
    exit(0);
*/
    if (argc >= 2) {
	fd = open(argv[1], O_RDONLY|O_BINARY, 0);
	if (fd != -1) {
	    close(0);
	    dup(fd);
	    close(fd);
	}
    }
    for (ofs=0;; ofs+=n) {
	n = fread(buf, 1, sizeof buf, stdin);
	hexdump(buf, n, ofs);
	if (n < sizeof buf)
	    break;
	putchar('\n');
    }

    return 0;
}
