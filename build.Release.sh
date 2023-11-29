PATH_NAME=$(dirname $(realpath $0))
cmake $PATH_NAME -DCMAKE_BUILD_TYPE=Release && make -j16
