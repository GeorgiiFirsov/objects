#
# Include directories
#
set(OBJECTS_SIMPLE_INCLUDE_DIRECTORIES ${OBJECTS_GENERIC_INCLUDE_DIRECTORIES})

#
# Directories
#
set(OBJECTS_SIMPLE_ROOT ${OBJECTS_EXAMPLES_ROOT}/simple)

#
# Lists of all sources
#
set(OBJECTS_SIMPLE_HEADER_FILES ${OBJECTS_EXAMPLES_COMMON_HEADER_FILES})

set(OBJECTS_SIMPLE_SOURCE_FILES ${OBJECTS_SIMPLE_ROOT}/main.cpp)

set(OBJECTS_SIMPLE_SOURCES      ${OBJECTS_SIMPLE_HEADER_FILES} 
                                ${OBJECTS_SIMPLE_SOURCE_FILES})

#
# Executable itself
#
add_executable(simple ${OBJECTS_SIMPLE_SOURCES})

#
# Set include directories
#
target_include_directories(simple PRIVATE ${OBJECTS_SIMPLE_INCLUDE_DIRECTORIES})
