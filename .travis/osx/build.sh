mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/usr/local -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
make -j4
