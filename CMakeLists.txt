cmake_minimum_required(VERSION 3.10)
project(Valiant)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

find_package(SFML 2.5 COMPONENTS graphics audio network window system REQUIRED)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(valiant ${SOURCES})

target_link_libraries(valiant)