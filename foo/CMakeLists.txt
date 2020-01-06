# creating library using add_library command
# takes 2 parameters: 
# - name of the library, 
# - source code files required to compile that library

add_library("${PROJECT_NAME}" "")

# Come back to this later..
# - Adding an alias for our target
add_library(Foo::Foo ALIAS "${PROJECT_NAME}")
# ^-- this allows us to refer to Foo as Foo::Foo


# it also allows us to specify whether to build a static 
# library or a shared library
# eg: add_library("${PROJECT_NAME}" STATIC "")
#     add_library("${PROJECT_NAME}" SHARED "")
# we would be using BUILD_SHARED_LIBS variable (bool)

# next, specify the include directories
# parameters:
# - specify our target
# - include directories
# our build directories and install directories are different
# so we specify them separately using generator expression.
# generator expression -- $<KEY:VALUE>
target_include_directories("${PROJECT_NAME}" PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CURRENT_BINARY_DIR}>" # this will be understood later..
    "$<INSTALL_INTERFACE:include>"  # --> ${CMAKE_INSTALL_PREFIX}/include
)
# CMAKE_CURRENT_SOURCE_DIR -- the directory this CMakeLists.txt
# is in.
# "The way "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
#  expression works is, when we are in the build directory, that 
#  expression evaluates to that value, else returns an empty string"

# What is "PUBLIC"?
# -----------------
# In CMake we have something called "build requirements" and
# "usage requirements"
# PRIVATE   --> Build requirement, anything that is required to
#               compile our target
# INTERFACE --> Usage requirement, anything that is required to
#               link against our target     
# PUBLIC    --> PRIVATE + INTERFACE


# Modifying name of our target
# ----------------------------
# We would prefer our library to be named differently when it is
# built differently.
# If "Foo" is the name of the library in release, we would want
# "Foo-d" to be the name in debug, and if it is static, Foo-s-d

if(NOT BUILD_SHARED_LIBS)
    set(STATIC_POSTFIX "-s")
    
    # The following lines comes after cmake is run once..
    # We enter this block when we are building a static library
    # so we add our compile flags here:
    set_target_properties("${PROJECT_NAME}" PROPERTIES
        COMPILE_FLAGS -DFOO_STATIC_DEFINE
    )

    # Next we ties a few loose ends..
    # - adding an alias for our target

endif()

set_target_properties("${PROJECT_NAME}" PROPERTIES
    DEBUG_POSTFIX "${STATIC_POSTFIX}-d"
    RELEASE_POSTFIX "${STATIC_POSTFIX}"
    MINSIZEREL_POSTFIX "${STATIC_POSTFIX}-mr"
    RELWITHDEBUGINFO_POSTFIX "${STATIC_POSTFIX}-rd"
)

# GO TO line 92

# For DLL files to work we need to export it with DLL_EXPORT and
# import it with DLL_IMPORT macros. CMake can generate these
# macros for us.
include("GenerateExportHeader") # so that we can use the upcoming macro ...
generate_export_header("${PROJECT_NAME}")
# ^-- macro will create a file called foo_export.h
# foo_export.h 's path is ${CURRENT_BINARY_DIR}/foo_export.h
# we would install this export file..
install(FILES "${CURRENT_BINARY_DIR}/foo_export.h" DESTINATION "include")
# since our export file is created inside ${CURRENT_BINARY_DIR}
# it needs to be included in the list of include directories

# Now we tell CMake about the include and src subdirectories
add_subdirectory("include")
add_subdirectory("src")

# GO TO TOP/include/CMakeLists.txt