SRC_DIR = ./src
BUILD_DIR = ./build
TARGET_EXECUTABLE = xorist

CC = cc
CFLAGS = -O2

SOURCE_FILES := $(shell find $(SRC_DIR) -name "*.c")
OBJECT_FILES := $(SOURCE_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# How to build target executable
$(BUILD_DIR)/$(TARGET_EXECUTABLE): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $(BUILD_DIR)/$(TARGET_EXECUTABLE)

# How to build all object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -r ./build/*
