R=$HOME/ril-build
NDK=$R/android-ndk-r28c/toolchains/llvm/prebuilt/linux-x86_64
CXX="$NDK/bin/aarch64-linux-android35-clang++"
CC="$NDK/bin/aarch64-linux-android35-clang"
AR=$NDK/bin/llvm-ar
B=$HOME/los/frameworks/native/libs/binder/ndk
INC="-I$R/gen/include -I$B/include_platform -I$B/include_ndk -I$B/include_cpp"
CXXFLAGS="-std=c++20 -O2 -fPIC -Wno-unused-parameter $INC -DBINDER_STABILITY_SUPPORT"
