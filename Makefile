CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS = -pthread

SRC = src/main.c \
      src/input.c \
      src/parser.c \
      src/process.c \
      src/builtin.c \
      src/signals.c \
      src/pipes.c \
      src/redirect.c \
      src/thread.c \


TARGET = bin/shellforge

all: $(TARGET) bin/deadlock

$(TARGET):
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

bin/deadlock:
	mkdir -p bin
	$(CC) $(CFLAGS) src/deadlock.c $(LDFLAGS) -o bin/deadlock

run: $(TARGET)
	./$(TARGET)

asan:
	$(CC) $(CFLAGS) -fsanitize=address $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -rf bin/*

.PHONY: all run clean asan
