#!/usr/bin/env bash

set -e
if [ ! -e build ]; then
    mkdir -p build
fi

#OPT=-O3
OPT="-g -O2"
#DISASSEMBLY='-S -masm=intel'
#ASAN="-fsanitize=address -fno-omit-frame-pointer -fsanitize-address-use-after-scope -fsanitize=undefined"
#ASAN_LDFLAGS="-fsanitize=address "
CXXFLAGS="$CXXFLAGS -std=c++98 -Wall -Weverything -pedantic -Wno-global-constructors -Isrc -I. $ASAN"
LDFLAGS="$ASAN_LDFLAGS"
ARCH=-m64

# Use pedantic flags when compiling jctest tests
echo "COMPILING WITH JCTEST"
PLATFORM=x86_64-darwin
PREFIX=jctest

function compile_test {
    clang++ -o ./build/${PREFIX}_test_params.o $OPT $DISASSEMBLY $ARCH $CXXFLAGS -c test/jctest/test_params.cpp
    clang++ -o ./build/${PREFIX}_main.o $OPT $DISASSEMBLY $ARCH $CXXFLAGS -c test/jctest/main.cpp
    clang++ -o ./build/${PREFIX}_params $OPT $ARCH $LDFLAGS ./build/${PREFIX}_main.o ./build/${PREFIX}_test_params.o
}

time compile_test 

if [ "Darwin" == `uname` ]; then
    echo ""
    echo "COMPILING WITH GTEST"

    GTESTDIR=./test/external/gtest
    PREFIX=gtest
    CXXFLAGS="-Wall -std=c++11 -Wno-deprecated-declarations -Isrc -I. -DUSE_GTEST -I${GTESTDIR}/include"
    LDFLAGS="-L${GTESTDIR}/lib/$PLATFORM -lgtest"

    time compile_test
fi

# Use less strict flags when compiling "regular" c++

CXXFLAGS="-Wno-sign-conversion -Wno-old-style-cast -Wno-weak-vtables  $CXXFLAGS"

clang++ -o ./build/test $OPT $DISASSEMBLY $ARCH -std=c++14 $CXXFLAGS $ASAN test/main.cpp
