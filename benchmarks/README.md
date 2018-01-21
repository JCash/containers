# How to generate the benchmarks

    $ ./compile_clang.sh array
    $ ./benchmark.sh array      # Outputs ./build/benchmarks/array.txt
    $ python makereport.py ./build/benchmarks/array.txt > report.txt
    $ python render.py report.txt ../images/array
    $ python markdown.py jc::Array array report.txt > benchmarks_array.md

# Benchmarks

* [HashTable](./benchmarks_ht.md)
* [Array](./benchmarks_array.md)