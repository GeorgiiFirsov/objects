cmake_minimum_required(VERSION 3.0.0)
project(objects VERSION 0.1.2)

#
# Global config
#
set(CMAKE_CXX_STANDARD 17)

#
# Options
#
option(OBJECTS_ENABLE_TESTING      "Enable testing of objects library." ON)
option(OBJECTS_ENABLE_EXAMPLES     "Enable building examples for objects library." ON)
option(OBJECTS_ENABLE_DOCS         "Enable building docs for objects library." ON)
option(OBJECTS_ENABLE_GH_DOCS_ONLY "Building documentation only (used by GitHub Actions)" OFF)

#
# Configuration
#
if (OBJECTS_ENABLE_GH_DOCS_ONLY)

    #
    # Here we build GitHub documentation only
    #

    set(OBJECTS_BUILD_TESTS    OFF)
    set(OBJECTS_BUILD_EXAMPLES OFF)
    set(OBJECTS_BUILD_DOCS     ON)
    set(OBJECTS_BUILD_GH_DOCS  ON)

    message(NOTICE "[${CMAKE_PROJECT_NAME}] Building GitHub documentation only. Flags OBJECTS_ENABLE_TESTING and OBJECTS_ENABLE_EXAMPLES are ignored")

else (OBJECTS_ENABLE_GH_DOCS_ONLY)

    #
    # Check if at leas one target is selected
    #

    if (NOT OBJECTS_ENABLE_TESTING AND NOT OBJECTS_ENABLE_EXAMPLES AND NOT OBJECTS_ENABLE_DOCS)
        message(WARNING "No target selected. Maybe you need to verify configuration flags")
        return()
    endif (NOT OBJECTS_ENABLE_TESTING AND NOT OBJECTS_ENABLE_EXAMPLES AND NOT OBJECTS_ENABLE_DOCS)

    #
    # Now dispatch targets
    #

    if (OBJECTS_ENABLE_TESTING)
        set(OBJECTS_BUILD_TESTS ON)
    else (OBJECTS_ENABLE_TESTING)
        set(OBJECTS_BUILD_TESTS OFF)
    endif (OBJECTS_ENABLE_TESTING)

    if (OBJECTS_ENABLE_EXAMPLES)
        set(OBJECTS_BUILD_EXAMPLES ON)
    else (OBJECTS_ENABLE_EXAMPLES)
        set(OBJECTS_BUILD_EXAMPLES OFF)
    endif (OBJECTS_ENABLE_EXAMPLES)

    if (OBJECTS_ENABLE_DOCS)
        set(OBJECTS_BUILD_DOCS    ON)
        set(OBJECTS_BUILD_GH_DOCS OFF)
    else (OBJECTS_ENABLE_DOCS)
        set(OBJECTS_BUILD_DOCS    OFF)
        set(OBJECTS_BUILD_GH_DOCS OFF)
    endif (OBJECTS_ENABLE_DOCS)

endif (OBJECTS_ENABLE_GH_DOCS_ONLY)

#
# Print current configuration
#
message(NOTICE "[${CMAKE_PROJECT_NAME}] Building tests: ${OBJECTS_BUILD_TESTS}")
message(NOTICE "[${CMAKE_PROJECT_NAME}] Building examples: ${OBJECTS_BUILD_EXAMPLES}")
message(NOTICE "[${CMAKE_PROJECT_NAME}] Building docs: ${OBJECTS_BUILD_DOCS} (for GitHub: ${OBJECTS_BUILD_GH_DOCS})")

#
# Global paths
#
set(OBJECTS_ROOT        ${CMAKE_SOURCE_DIR})
set(OBJECTS_LIB_INCLUDE ${OBJECTS_ROOT}/include)

#
# Generic include directories
#
set(OBJECTS_GENERIC_INCLUDE_DIRECTORIES ${OBJECTS_LIB_INCLUDE})

#
# Tests
#
if (OBJECTS_BUILD_TESTS)
    add_subdirectory(tests)
endif (OBJECTS_BUILD_TESTS)

#
# Examples
#
if (OBJECTS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif (OBJECTS_BUILD_EXAMPLES)

#
# Docs
#
if (OBJECTS_BUILD_DOCS)
    add_subdirectory(docs)
endif (OBJECTS_BUILD_DOCS)