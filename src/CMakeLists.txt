cmake_minimum_required(VERSION 3.16.3)
project(TBD_ProjectName)

add_subdirectory(lib)

find_package(fmt REQUIRED)

add_executable(TBD_project_name)
target_sources(TBD_project_name PRIVATE main.cpp)
target_link_libraries(TBD_project_name PRIVATE TBD_lib_project_name fmt::fmt)
