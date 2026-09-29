CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -I/usr/include/lua5.4
LDFLAGS = -llua5.4

BIN = bin
TARGET = $(BIN)/smake

SRC = src/main.c
OBJ = $(BIN)/main.o

.PHONY: all clean run

all: $(TARGET)

$(BIN):
	mkdir -p $(BIN)

$(OBJ): $(SRC) | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $< -o $@ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BIN)