cmake_minimum_required(VERSION 3.13)

project(cpp_tour LANGUAGES CXX C)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
# set(CMAKE_CXX_VISIBILITY_PRESET hidden)
# set(CMAKE_C_VISIBILITY_PRESET hidden)
# set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
# set(CMAKE_FIND_PACKAGE_RESOLVE_SYMLINKS TRUE)
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)


add_executable(chapter7 chapter7.cpp)
add_executable(std_array std_array.cpp)
add_executable(main main.cpp)
add_executable(function function.cpp)
target_compile_options(function PRIVATE 
  -g
  -std=c++20
)
add_executable(optional optional.cpp)
target_compile_options(optional PRIVATE -g -std=c++20)
add_executable(utility utility.cpp)
add_executable(vector vector.cpp)
add_executable(types types.cpp)
target_compile_options(utility PRIVATE -g -std=c++20 )
target_compile_options(vector PRIVATE -g -std=c++20 )
target_compile_options(types PRIVATE -g -std=c++20 )
target_include_directories(main PUBLIC SYSTEM  ${CMAKE_SOURCE_DIR}/utility)
