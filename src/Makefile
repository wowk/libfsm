CC=gcc
OBJS=test.o \
	 state-machine.o
TARGETS=test
CFLAGS= -g -Wall

all:$(OBJS)
	$(CC) $(OBJS) -o $(TARGETS) $(CFLAGS)

clean:
	-rm $(OBJS) $(TARGETS)
