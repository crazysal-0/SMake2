CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -Iinc -I/usr/include/lua5.4
LDFLAGS = -llua5.4

BIN = bin
TARGET = $(BIN)/smake

SRC = src/main.c src/api.c
OBJ = $(BIN)/main.o $(BIN)/api.o

.PHONY: all clean run

all: $(TARGET)

$(BIN):
	mkdir -p $(BIN)

$(BIN)/%.o: src/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BIN)