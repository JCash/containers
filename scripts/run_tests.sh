#!/usr/bin/env bash

set -e

TESTS="array hashtable algorithm rle bitarray ringbuffer"
if [[ $# -gt 0 ]] ; then
    TESTS="$*"
fi

for name in $TESTS; do
    time ./build/$name
done
