cmake_minimum_required(VERSION 3.30)

project(ZombieClickLess CXX)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Combine Warnings and Sanitizer flags
set(CXX_ALL_FLAGS ${CXX_WARNING_FLAGS} ${CXX_SANITIZERS_FLAGS})

# Include function to create C++20 Modules
include(cmake/CreateModuleLib.cmake)

add_subdirectory(src)

# Testing main
message("Copying assets folder into: ${CMAKE_BINARY_DIR}/assets")
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/)

# Add Game executable
add_executable(main)
target_sources(main PRIVATE src/main.cpp)
target_compile_features(main PUBLIC cxx_std_26)
target_compile_options(main PRIVATE ${CXX_ALL_FLAGS})
target_link_libraries(main PUBLIC TinyEngine ${CXX_SANITIZERS_FLAGS})
