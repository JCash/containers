#!/usr/bin/env bash

set -e
if [ ! -e build ]; then
    mkdir -p build
fi

#DISASSEMBLY="-S -masm=intel"
#PREPROCESS="-E"

if [ "$USE_ASAN" != "" ]; then
    if [ "$CXX" != "g++" ]; then
        ASAN="-fsanitize=address -fno-omit-frame-pointer -fsanitize-address-use-after-scope -fsanitize=undefined"
        ASAN_LDFLAGS="-fsanitize=address "
    fi
    echo Using ASAN
fi

if [ "$OPT" == "" ]; then
    OPT="-O2"
fi
echo Using OPT=$OPT

if [ "$STDVERSION" == "" ]; then
    STDVERSION=c++11 # jctest minimum
fi
echo Using -std=$STDVERSION


if [ "$CXX" == "" ]; then
    CXX=clang++
fi
echo Using CXX=$CXX  \"$($CXX --version | grep -e "version")\"

if [ "$ARCH" == "" ]; then
    ARCH=-m64
fi
echo Using ARCH=$ARCH

CXXFLAGS="$CXXFLAGS -g -std=$STDVERSION -Wall -fno-exceptions -Wno-old-style-cast -Isrc -I. -Itest $ASAN $PREPROCESS"
LDFLAGS="$ASAN_LDFLAGS -g"

if [ "$CXX" == "clang++" ]; then
    CXXFLAGS="$CXXFLAGS -Wall -Weverything -Wno-poison-system-directories -Wno-global-constructors"
fi

if [ "$STDVERSION" != "c++98" ]; then
    CXXFLAGS="$CXXFLAGS -Wno-zero-as-null-pointer-constant -Wno-c++98-compat -Wno-c++98-compat-pedantic"
fi

if [ "$STDVERSION" == "c++98" ]; then
    CXXFLAGS="$CXXFLAGS -Wno-suggest-destructor-override -Wno-suggest-override"
fi

function compile_test {
    local name=$1
    echo "COMPILING $name"
    clang++ -o ./build/test_${name}.o $OPT $DISASSEMBLY $ARCH $CXXFLAGS -c test/${name}.cpp
    clang++ -o ./build/${name} $OPT $ARCH $LDFLAGS ./build/test_${name}.o
}

TESTS="array hashtable algorithm rle bitarray"
if [[ $# -gt 0 ]] ; then
    TESTS="$*"
fi

for name in $TESTS; do
    time compile_test $name
done
