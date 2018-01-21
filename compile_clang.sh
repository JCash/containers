
set +e
mkdir -p build

#OPT=-O3
OPT="-g -O0"
#DISASSEMBLY='-S -masm=intel'
CXXFLAGS="$CXXFLAGS -Wall -Weverything -pedantic -Wno-old-style-cast -Wno-sign-conversion -Wno-padded -Wno-unused-macros -Wno-c++98-compat -Wno-implicit-fallthrough"
ARCH=-m64

#clang -o test -g -O0 -m64 -std=c99 -Wall -Weverything -Wno-float-equal -pedantic -Isrc test/list.c
clang++ -o ./build/test $OPT $DISASSEMBLY $ARCH -std=c++14 $CXXFLAGS -Isrc test/main.cpp
#clang++ -o main.txt -g -O0 -m64 -Wall -Weverything -pedantic -Isrc -E test/main.cpp
