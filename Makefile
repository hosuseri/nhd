CURRENT = 1
REVISION = 1
AGE = 1

VERSION = `expr $(CURRENT) - $(AGE)`.$(AGE).$(REVISION)
LT_VERINFO = $(CURRENT):$(REVISION):$(AGE)

TARGET_EXECUTABLE=hd.exe
TARGET_LIBRARY=libdump

CC=C:/usr/opt/mingw64/bin/cc
CFLAGS=-Wall -O2

all: $(TARGET_LIBRARY).la $(TARGET_EXECUTABLE)

clean:
	rm -f *~ $(TARGET_EXECUTABLE) $(TARGET_LIBRARY).la crc.o hexdump.o hd.o crc.lo hexdump.lo hd.lo
	rm -rf ./.libs

$(TARGET_EXECUTABLE): hd.lo crc.h hexdump.h $(TARGET_LIBRARY).la
	libtool --tag=CC --mode=link gcc -static -O -o $@ hd.lo $(TARGET_LIBRARY).la
	strip $@

$(TARGET_LIBRARY).la: crc.lo hexdump.lo
	libtool --tag=CC --mode=link gcc -O -o $@ crc.lo hexdump.lo -rpath /usr/local/lib \
		 -version-info $(LT_VERINFO)
#	strip ./.libs/$(TARGET_LIBRARY).so.$(VERSION)

.SUFFIXES:

.SUFFIXES: .c .lo

.c.lo:; libtool --tag=CC --mode=compile gcc -c $(CFLAGS) $<
