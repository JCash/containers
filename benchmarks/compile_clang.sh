set -e
mkdir -p build

SUFFIX=
DEFINES=
#SUFFIX=_big
#DEFINES=-DBIG_VALUE
#CXX=clang++
CXX='time clang++'

OPT='-g -O3'
ARCH='-arch x86_64'
#ARCH='-arch armv7 -miphoneos-version-min=6.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk'

ARGS="$DEFINES $OPT $ARCH -Wall -DNDEBUG -std=c++14 -stdlib=libc++ -Ihashtable -Ialgorithm -I. -framework Foundation"

FILES="helpers.cpp report.cpp memory.cpp hashtable/test_hashtable.cpp testmain.cpp"


# echo stl map $SUFFIX
# clang++ -o build/ht_stl_map$SUFFIX -DIMPL_STL_MAP -DIMPL_ALLOCATOR_STL -std=c++11 $ARGS $FILES

# echo stl unordered map $SUFFIX
# clang++ -o build/ht_stl_unordered_map$SUFFIX -DIMPL_STL_UNORDERED_MAP -DIMPL_ALLOCATOR_STL -std=c++11 $ARGS $FILES

#echo eastl hash_map $SUFFIX
#clang++ -o build/ht_eastl_hash_map$SUFFIX -DIMPL_EASTL_HASH_MAP -DIMPL_ALLOCATOR_EASTL -DIMPL_EASTL -I../../external/EASTL/include -I../../external/EASTL/test/packages/EABase/include/Common ../../external/EASTL/source/hashtable.cpp -std=c++11 $ARGS $FILES

#echo boost unordered_map $SUFFIX
#clang++ -o build/ht_boost_unordered_map$SUFFIX -DIMPL_BOOST_UNORDERED_MAP -DIMPL_ALLOCATOR_BOOST -DBOOST_CONTAINER_STATIC_LINK=1 -I../../external/boost/ ../../external/boost/libs/container/src/alloc_lib.c ../../external/boost/libs/container/src/dlmalloc.cpp -Wno-deprecated-declarations -std=c++11 $ARGS $FILES
#echo boost flat_map $SUFFIX
#clang++ -o build/ht_boost_flat_map$SUFFIX -DIMPL_BOOST_FLAT_MAP -DIMPL_ALLOCATOR_BOOST -DBOOST_CONTAINER_STATIC_LINK=1 -I../../external/boost ../../external/boost/libs/container/src/alloc_lib.c ../../external/boost/libs/container/src/dlmalloc.cpp -Wno-deprecated-declarations -std=c++11 $ARGS $FILES

#echo google sparse_hash_map $SUFFIX
#clang++ -o build/ht_google_sparse_hash_map$SUFFIX -DIMPL_GOOGLE_SPARSEHASHMAP -DIMPL_ALLOCATOR_STL -I../../external/sparsehash/src -std=c++11 $ARGS $FILES
# echo google dense_hash_map $SUFFIX
# clang++ -o build/ht_google_dense_hash_map$SUFFIX -DIMPL_GOOGLE_DENSEHASHMAP -DIMPL_ALLOCATOR_STL -I../../external/sparsehash/src -std=c++11 $ARGS $FILES

# echo ska flat_hash_map $SUFFIX
# clang++ -o build/ht_ska_flat_hash_map$SUFFIX -DIMPL_SKA_FLAT_HASH_MAP -DIMPL_ALLOCATOR_STL -I../../external/flat_hash_map -std=c++14 $ARGS $FILES

# echo dmHashTable $SUFFIX
# clang++ -o build/ht_dm_hashtable$SUFFIX -DIMPL_DM_HASHTABLE -DIMPL_ALLOCATOR_NEW -I../../external/dmhashtable -std=c++14 -std=c++11 $ARGS $FILES

# echo jc hashtable V2 $SUFFIX
# clang++ -o build/ht_jc_hashtable_v2$SUFFIX -DIMPL_JC_HASHTABLE_V2 -DIMPL_ALLOCATOR_NEW -std=c++11 $ARGS $FILES


# echo jc hashtable $SUFFIX
# clang++ -o build/ht_jc_hashtable$SUFFIX -DIMPL_JC_HASHTABLE -DIMPL_ALLOCATOR_NEW -std=c++11 $ARGS $FILES


FILES="helpers.cpp report.mm report.cpp memory.cpp algorithm/test_algorithm.cpp testmain.cpp"


echo stl algorithm
$CXX -o build/stl_algorithm -DIMPL_STL $ARGS $FILES

echo wiki algorithm
$CXX -o build/wiki_algorithm -DIMPL_WIKISORT -I/Users/mathiaswesterdahl/work/external/WikiSort $ARGS $FILES

echo ska algorithm
$CXX -o build/ska_algorithm -DIMPL_SKA -I/Users/mathiaswesterdahl/work/external/ska_sort $ARGS $FILES

echo jc algorithm
$CXX -o build/jc_algorithm -DIMPL_JC -I/Users/mathiaswesterdahl/work/external/kxsort $ARGS $FILES


