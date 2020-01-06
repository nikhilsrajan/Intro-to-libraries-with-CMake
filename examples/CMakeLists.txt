# creating an executable using add_executable command
add_executable("Example" "main.cpp")

# we link our example executable with the foo library
# using target_link_libraries command
target_link_libraries("Example" PRIVATE Foo::Foo)