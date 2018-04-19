#!/us/bin/env sh

cmake -H. -Bbuild -G"Visual Studio 15 2017 Win64" -DCMAKE_PREFIX_PATH=/c/Qt/5.10.1/msvc2017_64/lib/cmake
