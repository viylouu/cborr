#!/usr/bin/env bash

mkdir -p build

COMPILER="gcc"
CFLAGS="-std=c99 -Wall -Wextra -Iinclude -Ieng -lglfw -ldl -lm -lGL"
SRC_DIRS=("eng" "include")

TEST_BUILD=false
EXAMPLE=""

for arg in "$@"; do
    if [ "$arg" = "-t" ]; then
        TEST_BUILD=true
    else
        EXAMPLE="$arg"
    fi
done

if [ "$TEST_BUILD" = true ]; then
    COMPILER="tcc"
    CFLAGS+=" -DSTBI_NO_SIMD"
else
    CFLAGS+=" -O2 -flto"
fi

if [ -n "$EXAMPLE" ]; then
    SRC_DIRS+=("examples/$EXAMPLE")
else
    SRC_DIRS+=("src")
fi

FILES=()
for dir in "${SRC_DIRS[@]}"; do
    while IFS= read -r file; do
        FILES+=("$file")
    done < <(find "$dir" -name "*.c")
done

"$COMPILER" "${FILES[@]}" $CFLAGS -o out

#mkdir -p build

#tcc \
#    -lglfw -ldl -lm -lGL \
#    -DSTBI_NO_SIMD \
#    -Iinclude -Ieng \
#    examples/window/main.c \
#    eng/eng.c eng/draw/draw.c eng/dyn/dyn.c eng/mat/mat.c eng/phys/phys.c eng/shader/shader.c eng/tex/tex.c \
#    include/glad/glad.c \
#    -std=c99 \
#    -o build/out


./build/out

