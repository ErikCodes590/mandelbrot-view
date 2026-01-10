CC := gcc
CFLAGS := -Wall -O2
LDLIBS := -lSDL3

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

C_SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRC))

TARGET := $(BIN_DIR)/main

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $@ $(LDLIBS)
	@echo "Built $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@
	@echo "Compiled $@"

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Removed obj and bin files"

run: all
	@$(TARGET)
