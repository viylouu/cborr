# usage:
#   make path        -> build & run example `examples/path/main.c`
#   make win_path    -> build & run example `examples/path/main.c` for windows :onion:
#   make             -> build engine only
#   make sillywindows-> build engine only for windows :onion:

CC = clang
WINCC = x86_64-w64-mingw32-gcc

CFLAGS = -Wall -Wextra -std=c99 -O2 -Isrc -Iinclude -Ieng

LDFLAGS = -lglfw -lGL -lm -ldl -lpthread -lX11
WIN_LDFLAGS = -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32

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
$(EXAMPLES): %: examples/%/main.c $(ENGINE_OBJ)
	@mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $(ENGINE_OBJ) $< -o $(TARGET_DIR)/$@ $(LDFLAGS)
	./$(TARGET_DIR)/$@

# windows example: build only
win_%: examples/%/main.c $(ENGINE_OBJ)
	@mkdir -p $(TARGET_DIR)
	$(WINCC) $(CFLAGS) $(ENGINE_OBJ) $< -o $(TARGET_DIR)/$*.exe $(WIN_LDFLAGS)

# windows engine build only
sillywindows: $(ENGINE_OBJ)
	@mkdir -p $(TARGET_DIR)
	$(WINCC) $(CFLAGS) $(ENGINE_OBJ) -o $(TARGET_DIR)/engine.exe $(WIN_LDFLAGS)

# clean build artifacts
clean:
	rm -rf $(TARGET_DIR)

