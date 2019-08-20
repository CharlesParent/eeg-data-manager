CC := gcc
CFLAGS=-Wall -g -O0 -Iinclude -Ipthread#-Werror
LDFLAGS=-lrt -lpthread

all: main

launch:
	make all
	./main

main: main.o time_utils.o data_generators.o data_gatherers.o
	$(CC) $(LDFLAGS) $^ -o $@
clean:
	rm -f main *.o 
