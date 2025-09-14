#!/usr/bin/env bash

mkdir -p build

COMPILER="gcc"
CFLAGS="-std=c99 -Wall -Wextra -Icborr/include -Iinclude -Icborr -I. -D GLFW_BUILD_X11=1 -D GLFW_BUILD_WAYLAND=0"
SRC_DIRS=(".")

TEST_BUILD=false
WINDOWS_BUILD=false
EXAMPLE=""

if [[ ! "$OSTYPE" == "linux-gnu" ]]; then
    WINDOWS_BUILD=true # sowwy windows to linux ppl
fi

for arg in "$@"; do
    if [ "$arg" = "-t" ]; then
        TEST_BUILD=true
    elif [ "$arg" = "-w" ]; then
        WINDOWS_BUILD=true
    else
        EXAMPLE="$arg"
    fi
done

if [[ "$TEST_BUILD" == "true" ]]; then
    COMPILER="zig cc"
    CFLAGS+=" -O0 -g -DSTBI_NO_SIMD"
else
    CFLAGS+=" -O2 -flto"
fi

if [ "$WINDOWS_BUILD" = true ]; then
    [[ "$TEST_BUILD" == "false" ]] && COMPILER="x86_64-w64-mingw32-gcc"
    CFLAGS+=" -Linclude/LINK/glfw -lglfw3 -lm -lopengl32 -lgdi32 "
else
    CFLAGS+=" -lglfw -ldl -lm -lGL" #-LEGL -LX11
fi

if [ -n "$EXAMPLE" ]; then
    # assume we are in cborr
    SRC_DIRS=("." "examples/$EXAMPLE")
else
    if [ -f "./eng.c" ]; then
        SRC_DIRS=(".")
    else 
        SRC_DIRS=("cborr" "src")
    fi
fi

FILES=()
for dir in "${SRC_DIRS[@]}"; do
    while IFS= read -r file; do
        FILES+=("$file")
    done < <(find "$dir" -name "*.c" ! -path "*/examples/*")
done

if [ "$WINDOWS_BUILD" = true ]; then
    "$COMPILER" "${FILES[@]}" $CFLAGS -o build/out.exe
    if [[ "$OSTYPE" == "linux-gnu" ]]; then
        wine ./build/out.exe
    else
        ./build/out.exe
    fi
else
    echo -e "COMPILING: ${FILES[@]} \n"
    eval "$COMPILER" "${FILES[@]}" $CFLAGS -o build/out && ./build/out
fi

