CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC = src/main.c \
      src/input.c \
      src/parser.c \
      src/process.c \
      src/builtin.c \
      src/signals.c \
      src/pipes.c

TARGET = bin/shellforge

all: $(TARGET)

$(TARGET):
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

asan:
	$(CC) $(CFLAGS) -fsanitize=address $(SRC) -o $(TARGET)

clean:
	rm -rf bin/*
