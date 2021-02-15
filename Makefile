CC=gcc
CFLAGS=-lcurses
#DEPS = libncurses5

#%.o %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

mainfile: numattack.c
	$(CC) -o numattack numattack.c -w $(CFLAGS)

install:
	mkdir /opt/numattack
	cp ./numattack /opt/numattack/
	ln /opt/numattack/numattack /usr/games/numattack
uninstall:
	- rm -f /usr/games/numattack
	- rm -rf /opt/numattack/
clean:
	- rm ./numattack
