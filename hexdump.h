#ifndef __HEXDUMP_H__
#define __HEXDUMP_H__

#include "config.h"
#if HAVE_TYPES_H
#include <sys/types.h>
#else
#include "types.h"
#endif

void hexdump(void *s, int n, u_long ofs);

#endif  /* __HEXDUMP_H__ */
