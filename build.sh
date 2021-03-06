# This file is not meant to be executed
# It is just an example on how to build the project
mkdir build && cd build
conan install .. -b missing -s build_type=Debug

cmake .. -GNinja -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build . # Will set --config=Debug because of the conan install command used
