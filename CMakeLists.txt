cmake_minimum_required(VERSION 3.10)
project(Valiant)

set(CMAKE_CXX_STANDARD 17)

set(MYSQLCPPCONN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SqlLibs/mysqlLinux/include)
set(MYSQLCPPCONN_LIBRARY ${CMAKE_SOURCE_DIR}/SqlLibs/mysqlLinux/lib64)

include_directories(${MYSQLCPPCONN_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

find_package(SFML 2.5 COMPONENTS graphics audio network window system REQUIRED)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(valiant ${SOURCES})

find_library(MYSQLCPPCONN_LIB NAMES mysqlcppconn PATHS ${MYSQLCPPCONN_LIBRARY})
target_link_libraries(valiant sfml-graphics sfml-audio sfml-network sfml-window sfml-system ${MYSQLCPPCONN_LIB} ${Boost_LIBRARIES})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")