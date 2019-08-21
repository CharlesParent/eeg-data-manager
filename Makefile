CC := gcc
CFLAGS=-Wall -g -O2 -Iinclude -Ipthread#-Werror
LDFLAGS=-lrt -lpthread

all: main

launch:
	make all
	./main

main: main.o time_utils.o data_generators.o data_gatherers.o
	$(CC) $^ -o $@ $(LDFLAGS)
clean:
	rm -f main *.o 
