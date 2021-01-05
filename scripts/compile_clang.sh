#!/usr/bin/env bash

set -e
if [ ! -e build ]; then
    mkdir -p build
fi

#OPT=-O3
#OPT="-g -O2"
OPT="-g -O2"
#DISASSEMBLY="-S -masm=intel"
#PREPROCESS="-E"
#ASAN="-fsanitize=address -fno-omit-frame-pointer -fsanitize-address-use-after-scope -fsanitize=undefined"
#ASAN_LDFLAGS="-fsanitize=address "
CXXFLAGS="$CXXFLAGS -std=c++98 -Wall -Weverything -Wno-global-constructors -Wno-old-style-cast -Isrc -I. -Itest $ASAN $PREPROCESS"
LDFLAGS="$ASAN_LDFLAGS"
ARCH=-m64

# Use pedantic flags when compiling jctest tests
echo "COMPILING WITH JCTEST"
PLATFORM=x86_64-darwin
PREFIX=jc

function compile_test {
    local name=$1
    clang++ -o ./build/${PREFIX}_test_${name}.o $OPT $DISASSEMBLY $ARCH $CXXFLAGS -c test/${name}.cpp
    clang++ -o ./build/${PREFIX}_${name} $OPT $ARCH $LDFLAGS ./build/${PREFIX}_test_${name}.o
}

time compile_test array
time compile_test hashtable
time compile_test algorithm
