# https://www.youtube.com/watch?v=5i6uLMP5VcY

cmake_minimum_required(VERSION "3.0.0")

# Tieing more loose ends..
# Set target output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
# Adding BUILD_SHARED_LIBS variable to cache so that it need
# not be added manually anymore
option(BUILD_SHARED_LIBS "True when building shared library" True)


project("Foo")

# go to subdirectory "foo" and execute the CMakeLists.txt
# in that directory
add_subdirectory("foo")


# This is done after loose ends are tied up..
# To demonstrate that the library works we create a new
# subdirectory -- examples
add_subdirectory("examples")