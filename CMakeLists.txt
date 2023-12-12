cmake_minimum_required(VERSION 3.10)
project(Valiant)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# MySQL
set(MYSQLCPPCONN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SqlLibs/mysqlLinux/include)
set(MYSQLCPPCONN_LIBRARY ${CMAKE_SOURCE_DIR}/SqlLibs/mysqlLinux/lib64)
include_directories(${MYSQLCPPCONN_INCLUDE_DIR})
find_library(MYSQLCPPCONN_LIB NAMES mysqlcppconn PATHS ${MYSQLCPPCONN_LIBRARY})

# Boost
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# SFML
set(SFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SFML-2.5.1/include)
set(SFML_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib)
include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})

# Include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(valiant ${SOURCES})

# Link libraries
target_link_libraries(valiant ${MYSQLCPPCONN_LIB} ${Boost_LIBRARIES} sfml-graphics sfml-audio sfml-network sfml-window sfml-system)
