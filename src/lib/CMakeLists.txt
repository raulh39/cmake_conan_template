add_library(TBD_lib_project_name OBJECT)

target_sources(TBD_lib_project_name
  PRIVATE impl1.cpp)

# target_link_libraries(
#   TBD_lib_project_name
# )
target_include_directories(TBD_lib_project_name PUBLIC .)
