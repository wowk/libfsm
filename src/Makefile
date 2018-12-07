CC=gcc

all:
	$(CC) fsm.c -std=gnu11 -shared -o libfsm.so -I./ -Wall -Werror

install:
	mkdir -p /usr/local/include/fsm/
	mkdir -p /usr/local/lib/fsm/
	cp fsm.h /usr/local/include/fsm/
	cp libfsm.so /usr/local/lib/fsm/

