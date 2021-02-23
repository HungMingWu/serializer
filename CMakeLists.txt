CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
project(serializer)
add_executable(test 
    main.cpp
    memory_output_archive.cpp
    memory_input_archive.cpp
    struct_test.cpp
)
target_compile_features(test PUBLIC cxx_std_11)
