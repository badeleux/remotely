CC=gcc
LFLAGS=-g
BINDIR=./bin
SRCDIR=./src
UNIXSRCDIR=../unix_src

server: $(UNIXSRCDIR)/server.c
	$(CC) $(LFLAGS) $^ -o $(BINDIR)/$@

client: $(SRCDIR)/client.c 
	$(CC) $(LFLAGS) $^ -o $(BINDIR)/$@

uinput: $(SRCDIR)/uinput_handler.c
	$(CC) $(LFLAGS) $^ -o $(BINDIR)/$@  -Wall -framework ApplicationServices

