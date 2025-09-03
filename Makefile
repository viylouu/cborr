# compilers
CC = clang
WINCC = x86_64-w64-mingw32-gcc

# flags
CFLAGS = -Wall -Wextra -std=c99 -O2 -Isrc -Iinclude -Ieng
WIN_INCLUDE = -IC:/msys64/mingw64/include
WINCCFLAGS = $(CFLAGS) $(WIN_INCLUDE)

# linker flags
LDFLAGS = -lglfw -lGL -lm -ldl -lpthread -lX11
WIN_LDFLAGS = -lglfw -lopengl32 -lgdi32 -luser32 -lkernel32

# target dir
TARGET_DIR = build

# source files
SRC = $(wildcard src/*.c) $(shell find eng -name '*.c') $(shell find include -name '*.c')

# object files (mirror folder structure in build/)
ENGINE_OBJ = $(patsubst %.c,$(TARGET_DIR)/%.o,$(SRC))

# find examples
EXAMPLES = $(patsubst examples/%/main.c,%,$(wildcard examples/*/main.c))

.PHONY: all src clean

# default build: engine only
all: src

# build engine objects only
src: $(ENGINE_OBJ)

# generic rule for compiling C files
$(TARGET_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# linux example: build & run
$(EXAMPLES): %: examples/%/main.c src
	@mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $(ENGINE_OBJ) $< -o $(TARGET_DIR)/$@ $(LDFLAGS)
	./$(TARGET_DIR)/$@

# windows example: build only
win_%: examples/%/main.c src
	@mkdir -p $(TARGET_DIR)
	$(WINCC) $(WINCCFLAGS) $(ENGINE_OBJ) $< -o $(TARGET_DIR)/$*.exe $(WIN_LDFLAGS)

# windows engine build only
sillywindows: src
	@mkdir -p $(TARGET_DIR)
	$(WINCC) $(WINCCFLAGS) $(ENGINE_OBJ) -o $(TARGET_DIR)/engine.exe $(WIN_LDFLAGS)

# clean build artifacts
clean:
	rm -rf $(TARGET_DIR)

