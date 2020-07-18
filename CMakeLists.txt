CMAKE_MINIMUM_REQUIRED(VERSION 3.16.3)
project(socket-wrapper VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14")
set(source_dir "${PROJECT_SOURCE_DIR}/src/")
set(include_dir "${PROJECT_SOURCE_DIR}/include/")

file(GLOB source_files "${source_dir}/*.cpp")
file(GLOB header_files "${source_dir}/*.h")

include_directories(./include)
add_library(socket-wrapper SHARED ${source_files} ${header_files})