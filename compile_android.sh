#clang -o test -g -O0 -m64 -std=c99 -Wall -Weverything -Wno-float-equal -pedantic -Isrc test/list.c
#clang++ -o main -g -O0 -m64 -Wall -Weverything -pedantic -Isrc test/main.cpp
#clang++ -o main.txt -g -O0 -m64 -Wall -Weverything -pedantic -Isrc -E test/main.cpp

NDK_PLATFORM_VER=14
COMPILER_VERSION=4.9
ANDROID_NDK_ROOT=~/android/android-ndk-r10e
ANDROID_NDK_HOST=darwin-x86_64
ANDROID_SDK_ROOT=~/android/android-sdk-24.4.1

PREBUILD=$ANDROID_NDK_ROOT/toolchains/arm-linux-androideabi-$COMPILER_VERSION/prebuilt/$ANDROID_NDK_HOST

BIN=$PREBUILD/bin
INCLUDE=$ANDROID_NDK_ROOT/platforms/android-$NDK_PLATFORM_VER/arch-arm/usr/include

SYSROOT=$ANDROID_NDK_ROOT/platforms/android-$NDK_PLATFORM_VER/arch-arm

INCLUDE_STL=$ANDROID_NDK_ROOT/sources/cxx-stl/gnu-libstdc++/$COMPILER_VERSION/include
STL_LIB=$ANDROID_NDK_ROOT/sources/cxx-stl/gnu-libstdc++/$COMPILER_VERSION/libs/armeabi-v7a
INCLUDE_STL_ARCH=$STL_LIB/include

CC=$BIN/arm-linux-androideabi-g++

BUILDDIR=build
APP=test_android
INSTALL_DIR=/data/local/tmp

mkdir -p build

CFLAGS="-std=c++11 -g -O3 -gdwarf-2 -D__STDC_LIMIT_MACROS -Wall -fpic -ffunction-sections -fstack-protector -D__ARM_ARCH_5__ -D__ARM_ARCH_5T__ -D__ARM_ARCH_5E__ -D__ARM_ARCH_5TE__ -Wno-psabi -march=armv7-a -mfloat-abi=softfp -mfpu=vfp -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -fno-exceptions -funwind-tables -I$INCLUDE -I$INCLUDE_STL -I$INCLUDE_STL_ARCH --sysroot=$SYSROOT -DANDROID -Wa,--noexecstack -Isrc"
LDFLAGS="--sysroot=$SYSROOT -Wl,--fix-cortex-a8 -Wl,--no-undefined -Wl,-z,noexecstack -landroid -fpic -z text -L$STL_LIB -Wl,-Bstatic -Wl,-Bdynamic -lgnustl_static -lm -llog -lc -Wl,--no-undefined -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now"

#$CC $CFLAGS test/main.cpp -c -o $BUILDDIR/$APP.o
#$CC $BUILDDIR/$APP.o -o $BUILDDIR/$APP $LDFLAGS

$CC $CFLAGS test/main.cpp -c -o $BUILDDIR/$APP $LDFLAGS

$ANDROID_SDK_ROOT/platform-tools/adb push $BUILDDIR/$APP $INSTALL_DIR/$APP
$ANDROID_SDK_ROOT/platform-tools/adb shell chmod 777 $INSTALL_DIR/$APP

echo Installed to $INSTALL_DIR/$APP



