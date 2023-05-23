XORIST_SRC_DIR = ./src/xorist
BUILD_DIR = ./build
TARGET_EXECUTABLE = xorist

CC = cc
CFLAGS = -O2

SOURCE_FILES := $(shell find $(XORIST_SRC_DIR) -name "*.c")
OBJECT_FILES := $(SOURCE_FILES:$(XORIST_SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/$(TARGET_EXECUTABLE): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $(BUILD_DIR)/$(TARGET_EXECUTABLE)

$(BUILD_DIR)/%.o: $(XORIST_SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -r ./build/*
