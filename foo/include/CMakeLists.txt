set(FILES "")
set(SUBDIRECTORIES "Foo")
set(RELATIVE_PATH "include")

# We are going to use a loop to call add_subdirectory
# on all our SUBDIRECTORIES
foreach(VAR ${SUBDIRECTORIES})
    add_subdirectory(${VAR})
endforeach()

# Now we check if there are any files in this directory
# if FILES variable has anything in it, it would 
# evaluate to true
if(FILES)
    # using target_sources to add source files to our
    # target Foo
    target_sources("${PROJECT_NAME}" PRIVATE ${FILES})

    # We also want to install the files so we call
    # install command. Installs in 
    # ${CMAKE_INSTALL_PREFIX}/include
    install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()

# GO TO TOP/include/Foo/CMakeLists.txt