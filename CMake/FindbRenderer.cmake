# Try to find LibOBJ
# 
# Once done this will define:
#
#  BRENDERER_FOUND - library has been found
#  BRENDERER_INCLUDE_DIR - the include directory
#  BRENDERER_LIBRARY - link these to use Fontconfig
#
# Redistribution and use is allowed according to the terms of the BSD license.
#

if(BRENDERER_INCLUDE_DIR AND BRENDERER_LIBRARY)
   # in cache already
   SET(BRENDERER_FIND_QUIETLY TRUE)
endif()

IF(WIN32)
    FIND_PATH(BRENDERER_INCLUDE_DIR bRenderer.h
        PATHS $ENV{BRENDERER_ROOT})

    FIND_LIBRARY(BRENDERER_LIBRARY libbRenderer
        PATHS $ENV{BRENDERER_ROOT}/lib)
ELSE()
    FIND_PATH(BRENDERER_INCLUDE_DIR bRenderer.h
        PATHS /usr/local/include
              /usr/include)

    FIND_LIBRARY(BRENDERER_LIBRARY bRenderer
        PATHS /usr/local
              /usr
        PATH_SUFFIXES lib64 lib dylib)
ENDIF()

#message("BRENDERER_INCLUDE_DIR=${BRENDERER_INCLUDE_DIR}")
#message("BRENDERER_LIBRARY=${BRENDERER_LIBRARY}")

SET(BRENDERER_FOUND "NO")
IF(BRENDERER_INCLUDE_DIR AND BRENDERER_LIBRARY)
	SET(BRENDERER_FOUND "YES")
ENDIF()

INCLUDE(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(BRENDERER DEFAULT_MSG BRENDERER_INCLUDE_DIR BRENDERER_LIBRARY)

