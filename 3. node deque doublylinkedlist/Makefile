CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99
LDFLAGS =
SOURCES = doublelinkedlist.c node.c deque.c testdeque.c
EXECUTABLE = deque

build:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE) $(SOURCES)

clean:
	rm -f $(EXECUTABLE)

run: build
	./$(EXECUTABLE)

