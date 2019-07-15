#include <stdio.h>
#include "crc.h"

#define TRADMOD 1

#define BLANK ' '
#define PERIOD '.'

void hexdump(void *b, int n, u_long ofs)
{
    register u_char *p;
    register u_long i;
    register int j, k;
    int t;
    u_char *fp = NULL, *s, *stop;
    u_short acc = ofs;
    u_long m;

    stop = (u_char *)b + n;
    m = (n + 7) / 8 * 8;
    p = s = (u_char *)b;
    for (i=0; i < m; p=s+8) {
	if (!(i & 0x7F))
	    fp = p;
	if ((i & 7) == 0) {
	    s = p;
	    printf("%08lX ", ofs + i);
	}

	for (j=0; j < 8; j++) {
	    if (p >= stop)
		printf("   ");
	    else {
		t = (int)*p;
		printf("%02X ", t);
		if (p++ >= fp + 2)
		    acc = crc_step((u_char)t, acc);
		else {
		    acc <<= 8;
		    acc |= t;
		}
	    }
	}

	i += 8;

	for (p=s, t=j=0; j < 8; j++)
	    if (p < stop)
		t += (int)*p++;
	printf(": %02X / \"", t & 0xFF);
	for (p=s, j=0; j < 8; j++) {
	    if (p >= stop)
		t = BLANK;
	    else {
		t = (int)*p++;
		if (t < 0x20 || t >= 0x7F)
		    t = PERIOD;
	    }
	    printf("%c", (char)t);
	}
	printf("\"\n");

	if ((i & 0x7F) == 0 || i >= n) {
	    printf("-------------------------------------\n    SUM: ");
	    for (j=0; j < 8; j++) {
		p = fp + j;
		for (t=k=0; k < 16; k++, p+=8) {
		    if (p >= stop)
			break;
		    t += (int)*p;
		}
		printf("%02X ", t & 0xFF);
	    }
	    printf("%04X\n\n", acc);
	}
    }
}
