#
# Some additional directories
#
set(INCLUDE_DIRECTORIES ${COMMON_INCLUDE_DIRECTORIES})

#
# Lists of all sources
#
set(HEADER_FILES ${COMMON_HEADER_FILES} stream.h)
set(SOURCE_FILES main.cpp stream.cpp)
set(SOURCES ${HEADER_FILES} ${SOURCE_FILES})

#
# Executable itself
#
add_executable(streams ${SOURCES})

#
# Some useful and necessary properties
#
target_include_directories(streams PRIVATE ${INCLUDE_DIRECTORIES})
