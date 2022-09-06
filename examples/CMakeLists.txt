cmake_minimum_required(VERSION 3.0.0)
project(examples VERSION 0.1.0)

#
# Global config
#
set(CMAKE_CXX_STANDARD 17)

#
# Directory with Objects library
#
set(OBJECTS_DIRECTORY ../../include)
set(COMMON_INCLUDE_DIRECTORIES ${OBJECTS_DIRECTORY})
set(COMMON_HEADER_FILES ${OBJECTS_DIRECTORY}/objects.hpp)

#
# List of executables
#
add_subdirectory(simple)
#add_subdirectory(streams)
