project(glad
        LANGUAGES C
)

add_library(glad STATIC)

target_sources(glad
        PRIVATE
            src/glad.c

        PUBLIC
        FILE_SET HEADERS
        FILES
            include/glad/glad.h
            include/KHR/khrplatform.h
)

target_include_directories(glad PUBLIC include)

set_target_properties(glad PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        OBJECT_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin-int
)