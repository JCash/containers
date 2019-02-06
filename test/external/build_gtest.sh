#!/usr/bin/env bash

# build instructions from https://github.com/google/googletest/blob/master/googletest/README.md
set -e

if [ ! -e "./googletest" ]; then
    git clone https://github.com/google/googletest.git
fi
GTEST_DIR=./googletest/googletest

HOST_PLATFORM=`uname | tr '[:upper:]' '[:lower:]'`

PLATFORM=x86_64-${HOST_PLATFORM}
LIB_DIR=gtest/lib/${PLATFORM}
mkdir -p ${LIB_DIR}

echo "compiling gtest-all.cc"
clang++ -std=c++11 -O2 -I${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc
if [ -e "${LIB_DIR}/libgtest.a" ]; then
    rm ${LIB_DIR}/libgtest.a
    echo "removed" ${LIB_DIR}/libgtest.a
fi

echo "creating" ${LIB_DIR}/libgtest.a
ar rcsv ${LIB_DIR}/libgtest.a gtest-all.o
rm gtest-all.o

# PLATFORM=x86-${HOST_PLATFORM}
# g++ -std=c++11 -m32 -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc
# ar -rv ${LIB_DIR}/libgtest.a gtest-all.o
# rm gtest-all.o

rm -rf googletest
