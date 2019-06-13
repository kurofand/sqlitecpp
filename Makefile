CC=c++

CFLAGS=-std=c++17 -lsqlite3

all:
	$(CC) $(CFLAGS) main.cpp -o sqlite
