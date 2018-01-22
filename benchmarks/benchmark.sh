#!/usr/bin/env bash

set -e

TESTCATEGORY=$1
PLATFORM=$2

if [ "$TESTCATEGORY" == "" ]; then
    echo You must specify a category!
    exit 1
fi

if [ "$PLATFORM" == "" ]; then
    PLATFORM=`uname`
fi

BUILDDIR=./build/$TESTCATEGORY
OUTPUTDIR=./build/benchmarks
mkdir -p $OUTPUTDIR

function benchmark {
    local NAMES=$1
    local SERIES=$2

    local LOG=$OUTPUTDIR/$TESTCATEGORY.txt
    echo "# " > $LOG
    for i in $NAMES;
    do
        local NAME=${TESTCATEGORY}_$i
        local TEST=$BUILDDIR/$NAME

        for NUM in $SERIES;
        do
            echo $TEST $NUM
            $TEST $NUM >> $LOG
        done
    done
}


function benchmark_array {
    local SERIES=()
    count=100000
    while [ $count -le 1000000 ]
    do
         SERIES+="$count "
         ((count+=100000))
    done
    benchmark "stl eastl boost jc carray" "$SERIES"
}

case $TESTCATEGORY in
    "hashtable")    benchmark_hashtable ;;
    "array")        benchmark_array ;;
    "algorithm")    benchmark_algorithm ;;
esac
