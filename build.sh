#!/usr/bin/env bash

mkdir -p build
gcc -O3 -Wall $(pkg-config --cflags --libs lua54) -fPIC -shared \
    -Isrc src/ltime/*.c -o build/time.so $*
