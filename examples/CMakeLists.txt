cmake_minimum_required(VERSION 3.0.0)
project(examples VERSION 0.1.0)

#
# Global config
#
set(CMAKE_CXX_STANDARD 17)

#
# Some common paths 
#
set(OBJECTS_EXAMPLES_ROOT                       ${OBJECTS_ROOT}/examples)
set(OBJECTS_EXAMPLES_COMMON_INCLUDE_DIRECTORIES ${OBJECTS_GENERIC_INCLUDE_DIRECTORIES})
set(OBJECTS_EXAMPLES_COMMON_HEADER_FILES        ${OBJECTS_LIB_INCLUDE}/objects.hpp)

#
# List of executables
#
add_subdirectory(simple)
