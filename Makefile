# usage:
#   make path        -> build & run example `examples/path/main.c`
#   make win_path    -> build & run example `examples/path/main.c` for windows :onion:
#   make             -> build src only (src/)
#   make sillywindows-> build src only (src/) for windows :onion:

CC = clang
WINCC = x86_64-w64-mingw32-gcc

CFLAGS = -Wall -Wextra -std=c99 -O2 -Isrc
LDFLAGS = -lglfw -lGL -lm -ldl -lpthread -lX11

WIN_LDFLAGS = -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32

SRC = $(wildcard src/*.c)
ENGINE_OBJ = $(SRC:.c=.o)

TARGET_DIR = build
EXAMPLES = $(patsubst examples/%/main.c,%,$(wildcard examples/*/main.c))

.PHONY: all src clean

# default build: engine only
all: src

# build engine objects only
src: $(ENGINE_OBJ)

src/%.o: src/%.c
	@mkdir -p $(TARGET_DIR)
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

clean:
	rm -rf $(ENGINE_OBJ) $(TARGET_DIR)

