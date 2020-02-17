CC=gcc
CFLAGS=-lcurses
#DEPS = libncurses5

#%.o %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

mainfile: numattack.c
	$(CC) -o numattack numattack.c $(CFLAGS)

$(info ignore the warnings...)
