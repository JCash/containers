echo off

python3 --version 2>NUL
if errorlevel 1 goto errorNoPython
set TIMEIT=python %~dp0\timeit.py
goto hasPython
:errorNoPython
set TIMEIT
:hasPython

mkdir build

set FLAGS=/O2 /D_CRT_SECURE_NO_WARNINGS /nologo /D_HAS_EXCEPTIONS=0 /EHsc /W4 /wd4611 /Isrc /Itest

%TIMEIT% cl.exe %FLAGS% test\algorithm.cpp /link /out:.\build\algorithm.exe
%TIMEIT% cl.exe %FLAGS% test\array.cpp /link /out:.\build\array.exe
%TIMEIT% cl.exe %FLAGS% test\hashtable.cpp /link /out:.\build\hashtable.exe
%TIMEIT% cl.exe %FLAGS% test\rle.cpp /link /out:.\build\rle.exe
%TIMEIT% cl.exe %FLAGS% test\bitarray.cpp /link /out:.\build\bitarray.exe

del *.obj
