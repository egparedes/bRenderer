# CMake building script
#
# bRenderer: a basic real-time renderer framework using OpenGL 
# [ http://brenderer.b-dimension.com/ ]
#
# CMake script created by Enrique G. Paredes <egparedes@ifi.uzh.ch>
#                         VMMLab. University of Zürich. 2015

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

#
# ---- Project properties ----
#
project(brenderer)
set(BRENDERER_PROJECT_NAME bRenderer)
set(BRENDERER_ORGANIZATION_ID "ch.uzh.ifi.vmml")
set(BRENDERER_PROJECT_ID "${BRENDERER_ORGANIZATION_ID}.${PROJECT_NAME}")
set(BRENDERER_VERSION_MAJOR 0)
set(BRENDERER_VERSION_MINOR 1)
set(BRENDERER_VERSION_PATCH 0)
set(BRENDERER_VERSION_TYPE SNAPSHOT)
set(BRENDERER_VERSION_STRING "${BRENDERER_VERSION_MAJOR}.${BRENDERER_VERSION_MINOR}.${BRENDERER_VERSION_PATCH}-${BRENDERER_VERSION_TYPE}")

#
# ---- Global definitions ----
#
# Folder names
set(INCLUDE_DIRNAME "include")
set(SOURCE_DIRNAME "src")
set(EXTERNAL_DIRNAME "external")
set(EXTERNAL_SOURCE_DIRNAME "external-src")
set(BUILD_DIRNAME "build")
set(BIN_DIRNAME "bin")
set(LIB_DIRNAME "lib")
set(DOC_DIRNAME "doc")
set(DATA_DIRNAME "data")
set(EXPORT_DIRNAME "export")
set(INSTALL_DIRNAME "install")

# Inputs
set(BRENDERER_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/${INCLUDE_DIRNAME}")
set(BRENDERER_SOURCE_DIR "${PROJECT_SOURCE_DIR}/${SOURCE_DIRNAME}")
set(BRENDERER_EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/${EXTERNAL_DIRNAME}")
set(BRENDERER_EXTERNAL_SOURCE_DIR "${PROJECT_SOURCE_DIR}/${EXTERNAL_SOURCE_DIRNAME}")
set(BRENDERER_DOC_DIR "${PROJECT_SOURCE_DIR}/${DOC_DIRNAME}")
set(BRENDERER_DATA_DIR "${PROJECT_SOURCE_DIR}/${DATA_DIRNAME}")

# Outputs
set(BRENDERER_INSTALL_DIR "${PROJECT_SOURCE_DIR}/${INSTALL_DIRNAME}")
set(BRENDERER_LIBRARY_DIR "${PROJECT_BINARY_DIR}/${LIB_DIRNAME}")
set(BRENDERER_BINARY_DIR "${PROJECT_BINARY_DIR}/${BIN_DIRNAME}")
set(BRENDERER_EXPORT_DIR "${PROJECT_BINARY_DIR}/${EXPORT_DIRNAME}")

# Others
set(BRENDERER_ROOT_DIR "${PROJECT_SOURCE_DIR}")

#
# ---- External dependencies ----
#
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)
include(Utils)
include(bRenderer)

brenderer_set_custom_prefixes()
list(APPEND CMAKE_PREFIX_PATH ${BRENDERER_CUSTOM_PREFIXES})

#
# ---- Building configuration ----
#
# Source configuration
message(STATUS "BRENDERER_SOURCE_DIR set to ${BRENDERER_SOURCE_DIR}")
configure_sources(${BRENDERER_INCLUDE_DIR})
configure_sources(${BRENDERER_SOURCE_DIR})
configure_sources(${BRENDERER_DOC_DIR})

# Compilation and linking
set(LIBRARY_OUTPUT_PATH "${BRENDERER_LIBRARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${BRENDERER_BINARY_DIR}")

#get_cpp_options(global_cpp_flags all-warnings ) # c++11 all-warnings no-sign-compare no-unused-warnings)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${global_cpp_flags}")
#message(STATUS "CMAKE_CXX_FLAGS set to ${CMAKE_CXX_FLAGS}")

# Build included external sources
add_subdirectory(${BRENDERER_EXTERNAL_SOURCE_DIR})

# Build framework
add_subdirectory(src)

# Add Documentation Targets
#INCLUDE (DocumentationTargets)

# Build examples
add_subdirectory(examples)

#
# ---- Installation ----
#
set(CMAKE_INSTALL_PREFIX "${BRENDERER_INSTALL_DIR}")
