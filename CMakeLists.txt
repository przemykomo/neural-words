cmake_minimum_required(VERSION 3.16)
project(neural)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB_RECURSE SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*")

find_package(Threads)
add_executable(neural ${SRC})
target_link_libraries(neural Threads::Threads)
target_include_directories(neural PUBLIC include)

target_link_libraries(neural m)

file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${PROJECT_BINARY_DIR})
