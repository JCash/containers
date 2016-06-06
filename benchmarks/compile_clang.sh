
mkdir -p build

#SUFFIX=
#DEFINES=
SUFFIX=_big
DEFINES=-DBIG_VALUE

ARGS="$DEFINES -g -O3 -m64 -std=c++11 -Wall -Ihashtable -I. allocator.cpp helpers.cpp report.cpp hashtable/test_hashtable.cpp testmain.cpp"


#echo stl map
#clang++ -o build/ht_stl_map$SUFFIX -DIMPL_STL_MAP -DIMPL_ALLOCATOR_STL $ARGS
echo stl unordered map
clang++ -o build/ht_stl_unordered_map$SUFFIX -DIMPL_STL_UNORDERED_MAP -DIMPL_ALLOCATOR_STL $ARGS

echo eastl hash_map
clang++ -o build/ht_eastl_hash_map$SUFFIX -DIMPL_EASTL_HASH_MAP -DIMPL_ALLOCATOR_EASTL -I../../external/EASTL/include -I../../external/EASTL/test/packages/EABase/include/Common ../../external/EASTL/source/hashtable.cpp $ARGS

#echo boost unordered_map
#clang++ -o build/ht_boost_unordered_map$SUFFIX -DIMPL_BOOST_UNORDERED_MAP -DIMPL_ALLOCATOR_BOOST -DBOOST_CONTAINER_STATIC_LINK=1 -I../../external/boost/libs/config/include -I../../external/boost/libs/assert/include -I../../external/boost/libs/static_assert/include -I../../external/boost/libs/intrusive/include -I../../external/boost/libs/core/include -I../../external/boost/libs/move/include -I../../external/boost/libs/unordered/include -I../../external/boost/libs/container/include -I../../external/boost/libs/functional/include -I../../external/boost/libs/iterator/include -I../../external/boost/libs/mpl/include -I../../external/boost/libs/preprocessor/include -I../../external/boost/libs/detail/include -I../../external/boost/libs/tuple/include -I../../external/boost/libs/smart_ptr/include -I../../external/boost/libs/throw_exception/include -I../../external/boost/libs/integer/include -I../../external/boost/libs/type_traits/include ../../external/boost/libs/container/src/alloc_lib.c ../../external/boost/libs/container/src/dlmalloc.cpp -Wno-deprecated-declarations $ARGS
#echo boost flat_map
#clang++ -o build/ht_boost_flat_map$SUFFIX -DIMPL_BOOST_FLAT_MAP -DIMPL_ALLOCATOR_BOOST -DBOOST_CONTAINER_STATIC_LINK=1 -I../../external/boost/libs/config/include -I../../external/boost/libs/assert/include -I../../external/boost/libs/static_assert/include -I../../external/boost/libs/intrusive/include -I../../external/boost/libs/core/include -I../../external/boost/libs/move/include -I../../external/boost/libs/unordered/include -I../../external/boost/libs/container/include -I../../external/boost/libs/functional/include -I../../external/boost/libs/iterator/include -I../../external/boost/libs/mpl/include -I../../external/boost/libs/preprocessor/include -I../../external/boost/libs/detail/include -I../../external/boost/libs/tuple/include -I../../external/boost/libs/smart_ptr/include -I../../external/boost/libs/throw_exception/include -I../../external/boost/libs/integer/include -I../../external/boost/libs/type_traits/include ../../external/boost/libs/container/src/alloc_lib.c ../../external/boost/libs/container/src/dlmalloc.cpp -Wno-deprecated-declarations $ARGS

#echo google sparse_hash_map
#clang++ -o build/ht_google_sparse_hash_map$SUFFIX -DIMPL_GOOGLE_SPARSEHASHMAP -DIMPL_ALLOCATOR_STL -I../../external/sparsehash/src $ARGS
echo google dense_hash_map
clang++ -o build/ht_google_dense_hash_map$SUFFIX -DIMPL_GOOGLE_DENSEHASHMAP -DIMPL_ALLOCATOR_STL -I../../external/sparsehash/src $ARGS

echo dmHashTable
clang++ -o build/ht_dm_hashtable$SUFFIX -DIMPL_DM_HASHTABLE -DIMPL_ALLOCATOR_NEW -I../../external/dmhashtable $ARGS

echo jc hashtable
clang++ -o build/ht_jc_hashtable$SUFFIX -DIMPL_JC_HASHTABLE -DIMPL_ALLOCATOR_NEW $ARGS

echo jc hashtable 2
clang++ -o build/ht_jc_hashtable2$SUFFIX -DIMPL_JC_HASHTABLE_BIG -DIMPL_ALLOCATOR_NEW $ARGS
