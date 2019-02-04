#!/usr/bin/env bash

set +e
mkdir -p build

#OPT=-O3
OPT="-g -O1"
#DISASSEMBLY='-S -masm=intel'
ASAN="-fsanitize=address -fno-omit-frame-pointer -fsanitize-address-use-after-scope"
CXXFLAGS="$CXXFLAGS -std=c++98 -Wall -Weverything -pedantic -Wno-global-constructors"
ARCH=-m64

# Use pedantic flags when compiling jctest tests
# Use less strict flags when compiling "regular" c++

CXXFLAGS="-Wno-sign-conversion -Wno-old-style-cast -Wno-weak-vtables  $CXXFLAGS"

clang++ -o ./build/test $OPT $DISASSEMBLY $ARCH -std=c++14 $CXXFLAGS $ASAN -Isrc test/main.cpp
