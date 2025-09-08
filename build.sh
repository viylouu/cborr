#!/usr/bin/env bash

mkdir -p build

COMPILER="gcc"
CFLAGS="-std=c99 -Wall -Wextra -Iinclude -Ieng"
SRC_DIRS=("eng" "include")

TEST_BUILD=false
WINDOWS_BUILD=false
EXAMPLE=""

for arg in "$@"; do
    if [ "$arg" = "-t" ]; then
        TEST_BUILD=true
    elif [ "$arg" = "-w" ]; then
        WINDOWS_BUILD=true
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

if [[ "$OSTYPE" == "linux-gnu"  ]] && [[ "$WINDOWS_BUILD" == "true" ]]; then
    CFLAGS+=" -Linclude/LINK/glfw -lglfw3"
elif [[ "$OSTYPE" == "mysys" ]] || [[ "$OSTYPE" == "cygwin" ]] && [[ "$WINDOWS_BUILD" == "true" ]]; then
    CFLAGS+=" "
fi

if [ "$WINDOWS_BUILD" = true ]; then
    COMPILER="x86_64-w64-mingw32-gcc"
    CFLAGS+=" -Linclude/LINK/glfw -lglfw3 -lm -lopengl32 -lgdi32 "
else
    CFLAGS+=" -lglfw -ldl -lm -lGL"
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

if [ "$WINDOWS_BUILD" = true ]; then
    "$COMPILER" "${FILES[@]}" $CFLAGS -o build/out.exe
    if [[ "$OSTYPE" == "linux-gnu" ]]; then
        wine ./build/out.exe
    else
        ./build/out.exe
    fi
else
    "$COMPILER" "${FILES[@]}" $CFLAGS -o build/out && ./build/out
fi

