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

BUILDDIR=build/$TESTCATEGORY
mkdir -p $BUILDDIR

EXTERNALDIR=../../external

EASTL_INCLUDE="${EXTERNALDIR}/EASTL/include"
BOOST_INCLUDE="${EXTERNALDIR}/boost"

SUFFIX=
DEFINES=
#SUFFIX=_big
#DEFINES=-DBIG_VALUE
#CXX=clang++
CXX='time clang++'

OPT='-g -O3 -DNDEBUG'
#OPT='-g -O0 -fsanitize=address -fno-omit-frame-pointer'

ARGS="$DEFINES $OPT $ARCH -Wall -std=c++14 -stdlib=libc++ -I../src -Ihashtable -Ialgorithm -I. -framework Foundation"

ARCH='-arch x86_64'
REPORT_PLATFORM_IMPL=""
if [ "$PLATFORM" == "ios" ]; then
    REPORT_PLATFORM_IMPL="report.mm"
    ARCH='-arch armv7 -miphoneos-version-min=6.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk'
fi

FILES="helpers.cpp $REPORT_PLATFORM_IMPL report.cpp memory.cpp $TESTCATEGORY/test_$TESTCATEGORY.cpp testmain.cpp"

function compile_hashtable {
    echo "temporarily disabled"
    # echo stl map $SUFFIX
    # clang++ -o $BUILDDIR/ht_stl_map$SUFFIX -DIMPL_STL_MAP -DIMPL_ALLOCATOR_STL -std=c++11 $ARGS $FILES

    # echo stl unordered map $SUFFIX
    # clang++ -o $BUILDDIR/ht_stl_unordered_map$SUFFIX -DIMPL_STL_UNORDERED_MAP -DIMPL_ALLOCATOR_STL -std=c++11 $ARGS $FILES

    #echo eastl hash_map $SUFFIX
    #clang++ -o $BUILDDIR/ht_eastl_hash_map$SUFFIX -DIMPL_EASTL_HASH_MAP -DIMPL_ALLOCATOR_EASTL -DIMPL_EASTL -I../../external/EASTL/include -I../../external/EASTL/test/packages/EABase/include/Common ../../external/EASTL/source/hashtable.cpp -std=c++11 $ARGS $FILES

    #echo boost unordered_map $SUFFIX
    #clang++ -o $BUILDDIR/ht_boost_unordered_map$SUFFIX -DIMPL_BOOST_UNORDERED_MAP -DIMPL_ALLOCATOR_BOOST -DBOOST_CONTAINER_STATIC_LINK=1 -I../../external/boost/ ../../external/boost/libs/container/src/alloc_lib.c ../../external/boost/libs/container/src/dlmalloc.cpp -Wno-deprecated-declarations -std=c++11 $ARGS $FILES
    #echo boost flat_map $SUFFIX
    #clang++ -o $BUILDDIR/ht_boost_flat_map$SUFFIX -DIMPL_BOOST_FLAT_MAP -DIMPL_ALLOCATOR_BOOST -DBOOST_CONTAINER_STATIC_LINK=1 -I../../external/boost ../../external/boost/libs/container/src/alloc_lib.c ../../external/boost/libs/container/src/dlmalloc.cpp -Wno-deprecated-declarations -std=c++11 $ARGS $FILES

    #echo google sparse_hash_map $SUFFIX
    #clang++ -o $BUILDDIR/ht_google_sparse_hash_map$SUFFIX -DIMPL_GOOGLE_SPARSEHASHMAP -DIMPL_ALLOCATOR_STL -I../../external/sparsehash/src -std=c++11 $ARGS $FILES
    # echo google dense_hash_map $SUFFIX
    # clang++ -o $BUILDDIR/ht_google_dense_hash_map$SUFFIX -DIMPL_GOOGLE_DENSEHASHMAP -DIMPL_ALLOCATOR_STL -I../../external/sparsehash/src -std=c++11 $ARGS $FILES

    # echo ska flat_hash_map $SUFFIX
    # clang++ -o $BUILDDIR/ht_ska_flat_hash_map$SUFFIX -DIMPL_SKA_FLAT_HASH_MAP -DIMPL_ALLOCATOR_STL -I../../external/flat_hash_map -std=c++14 $ARGS $FILES

    # echo dmHashTable $SUFFIX
    # clang++ -o $BUILDDIR/ht_dm_hashtable$SUFFIX -DIMPL_DM_HASHTABLE -DIMPL_ALLOCATOR_NEW -I../../external/dmhashtable -std=c++14 -std=c++11 $ARGS $FILES

    # echo jc hashtable V2 $SUFFIX
    # clang++ -o $BUILDDIR/ht_jc_hashtable_v2$SUFFIX -DIMPL_JC_HASHTABLE_V2 -DIMPL_ALLOCATOR_NEW -std=c++11 $ARGS $FILES


    # echo jc hashtable $SUFFIX
    # clang++ -o $BUILDDIR/ht_jc_hashtable$SUFFIX -DIMPL_JC_HASHTABLE -DIMPL_ALLOCATOR_NEW -std=c++11 $ARGS $FILES

}

function compile_algorithm {
    echo ${TESTCATEGORY}: stl
    $CXX -o $BUILDDIR/${TESTCATEGORY}_stl -DIMPL_STL $ARGS $FILES

    echo ${TESTCATEGORY}: wiki
    $CXX -o $BUILDDIR/${TESTCATEGORY}_wiki -DIMPL_WIKISORT -I$EXTERNALDIR/WikiSort $ARGS $FILES

    echo ${TESTCATEGORY}: ska
    $CXX -o $BUILDDIR/${TESTCATEGORY}_ska -DIMPL_SKA -I$EXTERNALDIR/ska_sort $ARGS $FILES

    echo ${TESTCATEGORY}: jc
    $CXX -o $BUILDDIR/${TESTCATEGORY}_jc -DIMPL_JC -I$EXTERNALDIR/kxsort $ARGS $FILES
}

function compile_array {
    if [ -d "$BOOST_INCLUDE" ]; then
        echo $TESTCATEGORY: boost
        $CXX -o $BUILDDIR/${TESTCATEGORY}_boost -DIMPL_BOOST -I$BOOST_INCLUDE/container/include -I$BOOST_INCLUDE/move/include -I$BOOST_INCLUDE/assert/include -I$BOOST_INCLUDE/static_assert/include -I$BOOST_INCLUDE/intrusive/include -I$BOOST_INCLUDE/core/include -I$BOOST_INCLUDE/config/include $ARGS $FILES
    fi

    echo $TESTCATEGORY: stl
    $CXX -o $BUILDDIR/${TESTCATEGORY}_stl -DIMPL_STL $ARGS $FILES

    if [ -d "$EASTL_INCLUDE" ]; then
        echo $TESTCATEGORY: eastl
        $CXX -o $BUILDDIR/${TESTCATEGORY}_eastl -DIMPL_EASTL -I$EASTL_INCLUDE -I$EASTL_INCLUDE/../test/packages/EABase/include/Common $ARGS $FILES
    fi

    echo $TESTCATEGORY: jc
    $CXX -o $BUILDDIR/${TESTCATEGORY}_jc -DIMPL_JC $ARGS $FILES
}


case $TESTCATEGORY in
    "hashtable")    compile_hashtable ;;
    "array")        compile_array ;;
    "algorithm")    compile_algorithm ;;
esac



