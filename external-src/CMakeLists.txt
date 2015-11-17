#
# CMake building script for external libs
#
# Created by Enrique G. Paredes <egparedes@ifi.uzh.ch>
#            VMMLab. University of Zürich. 2015
#

message(STATUS "\nAutomatic configuration and building of external libraries")

file(GLOB files ${CMAKE_CURRENT_SOURCE_DIR}/*)
list(SORT files)
foreach(dir ${files})
    if(IS_DIRECTORY ${dir})
        get_filename_component(dir_name ${dir} NAME)
        message(STATUS "---- ${dir_name} ----")
        add_subdirectory(${dir} ${PROJECT_BINARY_DIR}/${dir_name})
        message(STATUS "--------")
    endif()
endforeach()
