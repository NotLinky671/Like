cmake_minimum_required(VERSION 3.23)

project(Like)

add_subdirectory(Like)
add_subdirectory(Sandbox)

set_target_properties(Like PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        OBJECT_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin-int
)

target_compile_features(Like PRIVATE cxx_std_17)