CC=c++

CFLAGS=-std=c++20 -lsqlite3

all:
	$(CC) $(CFLAGS) main.cpp -o sqlite
