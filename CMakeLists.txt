cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
add_subdirectory(googletest)

include_directories(googletest/googletest/include)
add_executable(ft_containers main.cpp List.hpp Stack.hpp Vector.hpp Iterator.hpp Queue.hpp)
target_link_libraries(ft_containers gtest gtest_main)