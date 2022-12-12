#
# Configuration flags
#
if (OBJECTS_BUILD_GH_DOCS)
    #
    # For GitHub docs we generate pretty diagrams
    #

    set(OBJECTS_DOXYGEN_HAVE_DOT YES)
else (OBJECTS_BUILD_GH_DOCS)
    #
    # Othrewise -- default ones
    #

    set(OBJECTS_DOXYGEN_HAVE_DOT NO)
endif (OBJECTS_BUILD_GH_DOCS)

#
# Setup paths
#
set(OBJECTS_DOCS_VERSION              ${CMAKE_PROJECT_VERSION})
set(OBJECTS_DOCS_ROOT                 ${OBJECTS_ROOT}/docs)
set(OBJECTS_DOCS_DOXYGEN_AWESOME_ROOT ${OBJECTS_DOCS_ROOT}/doxygen-awesome-css)
set(OBJECTS_DOCS_DOXYGEN_IN           ${OBJECTS_DOCS_ROOT}/Doxyfile.in)
set(OBJECTS_DOCS_DOXYGEN_OUT          ${OBJECTS_DOCS_ROOT}/Doxyfile)

#
# And here we go...
#
message("[${CMAKE_PROJECT_NAME}] Configuring doxygen...")
configure_file(${OBJECTS_DOCS_DOXYGEN_IN} ${OBJECTS_DOCS_DOXYGEN_OUT} @ONLY)

#
# In case of GitHub docs we only need a configuration file to be 
# generated, so we quit here in this case
#
if (OBJECTS_BUILD_GH_DOCS)
    message(NOTICE "[${CMAKE_PROJECT_NAME}] Doxyfile is generated, but OBJECTS_BUILD_GH_DOCS is set, nothing else will be performed")
    message(NOTICE "[${CMAKE_PROJECT_NAME}] Doxyfile is located here: '${OBJECTS_DOCS_DOXYGEN_OUT}'")
    return()
endif (OBJECTS_BUILD_GH_DOCS)

#
# Otherwise we need to find Doxygen
#
find_package(Doxygen)

#
# Check if we have Doxygen installed
#
if (NOT DOXYGEN_FOUND )
    message(WARNING "[${CMAKE_PROJECT_NAME}] Doxygen need to be installed to generate the doxygen documentation")
    return()
endif() 

#
# Custom target for building documentation
#
add_custom_target(OBJECTS_docs ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${OBJECTS_DOCS_DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating documentation with Doxygen"
    VERBATIM)