CC = gcc
CFLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
VALGRIND = help50 valgrind --leak-check=full --track-origins=yes --show-reachable=yes
CMD = grep ien 0

build: *.c
	$(CC) $(CFLAGS) -o grep *.c
	$(VALGRIND) ./$(CMD)

run: build