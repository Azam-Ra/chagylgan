cmake_minimum_required(VERSION 4.1.0)

project(chagylgan VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(chag src/main.cpp)

find_package(utf8cpp CONFIG REQUIRED)
find_package(LLVM CONFIG REQUIRED)
target_link_libraries(chag PRIVATE utf8cpp::utf8cpp LLVMCore)

