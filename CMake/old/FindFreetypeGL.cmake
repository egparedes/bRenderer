# Try to find Freetype-GL
# 
# Once done this will define:
#
#  FREETYPEGL_FOUND - library has been found
#  FREETYPEGL_INCLUDE_DIR - the include directory
#  FREETYPEGL_LIBRARY - link these to use Fontconfig
#
# Redistribution and use is allowed according to the terms of the BSD license.
#

if(FREETYPEGL_INCLUDE_DIR AND FREETYPEGL_LIBRARY)
   # in cache already
   SET(Freetypegl_FIND_QUIETLY TRUE)
endif()

IF(WIN32)
    FIND_PATH(FREETYPEGL_INCLUDE_DIR freetype-gl.h
        PATHS $ENV{FREETYPEGL_ROOT}/lib
        DOC "The directory where freetype-gl.h resides")

    FIND_LIBRARY(FREETYPEGL_LIBRARY freetypegl
        PATHS $ENV{FREETYPEGL_ROOT}/lib
        DOC "The Freetype-GL library")
ELSE()
    FIND_PATH(FREETYPEGL_INCLUDE_DIR freetype-gl.h
        PATHS /usr/local/include
              /usr/include)

    FIND_LIBRARY(FREETYPEGL_LIBRARY freetypegl
        PATHS /usr/local
              /usr/X11
              /usr
        PATH_SUFFIXES lib64 lib dylib)
ENDIF()

SET(FREETYPEGL_FOUND "NO")
IF(FREETYPEGL_INCLUDE_DIR AND FREETYPEGL_LIBRARY)
	SET(FREETYPEGL_FOUND "YES")
ENDIF()

INCLUDE(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FreetypeGL DEFAULT_MSG FREETYPEGL_INCLUDE_DIR FREETYPEGL_LIBRARY)

