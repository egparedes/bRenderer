# Try to find LibOBJ
# 
# Once done this will define:
#
#  LIBOBJ_FOUND - library has been found
#  LIBOBJ_INCLUDE_DIR - the include directory
#  LIBOBJ_LIBRARY - link these to use Fontconfig
#
# Redistribution and use is allowed according to the terms of the BSD license.
#

if(LIBOBJ_INCLUDE_DIR AND LIBOBJ_LIBRARY)
   # in cache already
   SET(LIBOBJ_FIND_QUIETLY TRUE)
endif()

IF(WIN32)
    FIND_PATH(LIBOBJ_INCLUDE_DIR obj.hpp
        PATHS $ENV{LIBOBJ_ROOT}
        DOC "The directory where obj.hpp resides")

    FIND_LIBRARY(LIBOBJ_LIBRARY libobj
        PATHS $ENV{LIBOBJ_ROOT}/lib
        DOC "The LibOBJ library")
ELSE()
    FIND_PATH(LIBOBJ_INCLUDE_DIR obj.hpp
        PATHS /usr/local/include
              /usr/include)

    FIND_LIBRARY(LIBOBJ_LIBRARY obj
        PATHS /usr/local
              /usr/X11
              /usr
        PATH_SUFFIXES lib64 lib dylib)
ENDIF()

SET(LIBOBJ_FOUND "NO")
IF(LIBOBJ_INCLUDE_DIR AND LIBOBJ_LIBRARY)
	SET(LIBOBJ_FOUND "YES")
ENDIF()

INCLUDE(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBOBJ DEFAULT_MSG LIBOBJ_INCLUDE_DIR LIBOBJ_LIBRARY)

