# Skeleton project CMake + Conan + Catch2 tests
This C++ template is based on Mateusz Pusz's [CMake + Conan: 3 Years Later](https://youtu.be/mrSwJBJ-0z8) talk given at CppNow 2021.

The idea is to reuse it whenever you want to start a new project that uses [CMake](https://cmake.org/) and [Conan](https://conan.io/).

It also uses [fmt](https://github.com/fmtlib/fmt) and [Catch2](https://github.com/catchorg/Catch2) libraries as examples on how to integrate them.

## How to use it

First, you need to click the green **"Use this template"** button near the top of this page.

That will take you to Github's "Generate Repository" page.
Fill in a repository name and short description, and click "Create repository from template".
A new repository in your Github account will be created prepopulated with the contents of this project.

Now you can clone the project locally and modify it. For example:

    $ git clone https://github.com/<user>/<your_new_repo>.git

## First things to do

You surely want to modify all the "TBD" strings in the four CMakeLists.txt files that come with the project. These are:
- `TBD_ProjectName`: This should be the name of the project.
- `TBD_project_name`: Not to be confused with the previous one. This is the name of the executable to be created, while the previous one is the name of the project in CMake.
- `TBD_lib_project_name`: This CMake OBJECT library is going to be used both in the main executable and in the tests. A proper name is needed. Maybe "lib_core".
- `TBD_test_project_name`: This is the name of the executable used for the tests.

But there is an additional "TBD" string in the file test/tests_source.cpp that also needs to be modified:
- `TBD_test_case_name`: Select a proper Catch2 test name

## How to build the project

The build.sh script shows an example of the compilation of the full project.
In a nutshell:
```
mkdir build
cd build
conan install .. -b missing

cmake .. -GNinja -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build . --config Debug
```
Of course, the CMake generator shown, Ninja, is just one example. You can use any one you like.

Whenever you modify the contents of the file `conanfile.txt` you should execute again
```
conan install .. -b missing
```

Whenever you modify any of the `CMakeLists.txt`, `.h` or `.cpp` files, you only need to reexecute
```
cmake --build . --config Debug
```
You can use any other --config option, of course.

## How to add a new library

First, localize the library you want to use in [Conan Center] (https://conan.io/center/) and choose the version you need.

Add the Conan identifier to the `[requires]` section of `conanfile.txt`.
Execute 
```
cd .../build
conan install .. -b missing
```
This will add the new library to your local Conan repository.

Then you need to add a find_package() in the CMakeLists.txt file where you want to make the library available.

The first parameter to find_package() depends on the Conan recipe (I guess). For example, 
for "catch2/2.13.3" we need to use "find_package(Catch2 REQUIRED)", but for "fmt/6.2.0" we need to use
"find_package(fmt REQUIRED)".

In case of doubt, after the "conan install" has been reexecuted, you can take a look at the generated files "*Targets.cmake",
the prefix of those files is the parameter needed for find_package().

But that's not all. We also need to know the CMake target that find_package() exports in order to use it in the corresponding
target_link_libraries(). This is easier because Conan prints that name whenever, after adding the find_package(), you reexecute 
```
cmake -G Ninja ..
```
For example:
```
[cmake] -- Conan: Target declared 'fmt::fmt'
[cmake] -- Conan: Target declared 'Catch2::Catch2'
```

### Example: adding OpenSSL

In Conan Center we can [search for OpenSSL ](https://conan.io/center/openssl) to get this list of possible packages:
```
openssl/1.0.2s
openssl/1.0.2t
openssl/1.0.2u
openssl/1.1.0k
openssl/1.1.0l
openssl/1.1.1c
openssl/1.1.1d
openssl/1.1.1e
openssl/1.1.1f
openssl/1.1.1g
openssl/1.1.1h
openssl/1.1.1i
openssl/1.1.1j
openssl/1.1.1k
```
We select, for example, "openssl/1.1.1k" and add it to conanfile.txt:
```
[requires]
catch2/2.13.3
docopt.cpp/0.6.2
fmt/6.2.0
openssl/1.1.1k

[generators]
CMakeToolchain
CMakeDeps
```

When we execute
```
cd build
conan install .. -b missing
```
we should notice that the file "OpenSSLTargets.cmake" is created.

So we add this line to CMakeLists.txt:
```
find_package(OpenSSL REQUIRED)
```
and then `cmake -G Ninja ..` will show:
```
-- Conan: Component target declared 'OpenSSL::Crypto'
-- Conan: Component target declared 'OpenSSL::SSL'
```
So we just need to add any (or both) of those targets in a target_link_libraries() line.

## "src" directory

In his talk, Mateusz Pusz points out that it is a good idea to make the "src" compilable by itself.
This project respects that idea, so this is ok:
```
cd .../src
mkdir build
cd build
cmake .. -GNinja
cmake --build .
```
Please note, however, that if some find_package() is used in the src/CMakeLists.txt, it will not benefit from Conan.
