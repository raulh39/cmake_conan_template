find_package(Catch2 REQUIRED)

add_executable(TBD_test_project_name)
target_sources(TBD_test_project_name PRIVATE tests_source.cpp catch_main.cpp)
target_link_libraries(TBD_test_project_name PRIVATE TBD_lib_project_name Catch2::Catch2)
