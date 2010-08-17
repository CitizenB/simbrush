CC=gcc
# Note:  temporarily removed -O2 for debuggability
CFLAGS=-Wall -I /usr/include/PCSC -g
LD=gcc
LIBS=-lpthread -lpcsclite

OBJS=SIMbrush.o pcsc-wrappers.o dirtree.o utils.o xml-results.o bail.o gsm-constants.o
PROGRAM=SIMbrush

$(PROGRAM) : $(OBJS)
	$(LD) -o $(PROGRAM) $(OBJS) $(LIBS)

pcsc-wrappers.o : pcsc-wrappers.c pcsc-wrappers.h gsm-constants.h
	$(CC) $(CFLAGS) -c pcsc-wrappers.c

dirtree.o : dirtree.c dirtree.h gsm-constants.h
	$(CC) $(CFLAGS) -c dirtree.c

utils.o : utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

xml-results.o : xml-results.c
	$(CC) $(CFLAGS) -c xml-results.c

clean :
	rm -rf $(PROGRAM) $(OBJS) *~
