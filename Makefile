XORIST_SRC_DIR = ./src/xorist
BUILD_DIR = ./build

CC = cc
CFLAGS = -O2

SOURCE_FILES := $(shell find $(XORIST_SRC_DIR) -name "*.c")
OBJECT_FILES := $(SOURCE_FILES:$(XORIST_SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: build/breaker build/xorist

build/breaker: build/breaker.o build/br_main.o
	cc -O2 build/breaker.o build/br_main.o -o build/breaker

build/breaker.o: src/breaker/xorist-breaker.c
	cc -c -O2 src/breaker/xorist-breaker.c -o $@

build/br_main.o: src/breaker/main.c
	cc -c -O2 src/breaker/main.c -o $@

$(BUILD_DIR)/xorist: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $(BUILD_DIR)/xorist

$(BUILD_DIR)/%.o: $(XORIST_SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -r ./build/*
