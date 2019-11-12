CC = gcc
CFLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
CMD = heap

build: *.c
	$(CC) $(CFLAGS) -o heap *.c
	$(VALGRIND) ./$(CMD)

run: build