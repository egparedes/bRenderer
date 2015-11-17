# CMake building script
#
# Freetype-GL library by Nicolas P. Rougier [ https://github.com/rougier/freetype-gl ]
#
# CMake script created by Enrique G. Paredes <egparedes@ifi.uzh.ch>
#                         VMMLab. University of Zürich. 2015

set(lib_name freetypegl)
set(print_name Freetype-GL)

message(STATUS "Building ${print_name} library [${lib_name}]")
set(include_output_dir "${BRENDERER_EXPORT_DIR}/${lib_name}/${INCLUDE_DIRNAME}")
set(lib_output_dir "${BRENDERER_EXPORT_DIR}/${lib_name}/${LIB_DIRNAME}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BRENDERER_EXPORT_DIR}/${lib_name}/${LIB_DIRNAME}")

# ---- Compilation ----
file(GLOB_RECURSE source_files *.cpp *.c)
#message(STATUS "source_files set to ${source_files}")

add_library(${lib_name} ${source_files})
get_cc_options(c_flags fPIC)
add_definitions(${c_flags})
#message(STATUS "c_flags = ${c_flags}")

# ---- Dependencies ----
#find_package(GLFW REQUIRED)
find_package(Freetype REQUIRED)

include_directories(${include_output_dir} 
	                ${BRENDERER_INCLUDE_DIR} 
	                ${FREETYPE_INCLUDE_DIRS} 
	                ${GLFW_INCLUDE_DIR})
target_link_libraries(${lib_name} ${FREETYPE_LIBRARIES} ${GLFW_ALL_LIBRARIES})

# ---- Post-build exports ----
# Export binary output and vars
get_target_property(lib_output ${lib_name} LOCATION)
get_filename_component(lib_binary ${lib_output} NAME)

message(STATUS "Exporting ${print_name} headers")
set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}")
copy_file_hierarchy(${src_dir} ${include_output_dir} *.h *.hpp)
set(FREETYPEGL_INCLUDE_DIR "${include_output_dir}" 
	CACHE STRING "${print_name} library include path")

set(freetypegl_INCLUDE_DIRS ${FREETYPEGL_INCLUDE_DIR})
list(APPEND freetypegl_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
list(APPEND freetypegl_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIRS})
set(FREETYPEGL_INCLUDE_DIRS ${freetypegl_INCLUDE_DIRS} 
	CACHE STRING "${print_name} whole include paths")
#message("FREETYPEGL_INCLUDE_DIRS=${FREETYPEGL_INCLUDE_DIRS}\n")

message(STATUS "${print_name} binary objects [${lib_binary}] will be exported after compilation")
set(FREETYPEGL_LIBRARY "${lib_output_dir}/${lib_binary}" 
	CACHE STRING "${print_name} library binary")
set(fretypegl_all_LIBRARIES ${FREETYPEGL_LIBRARY})
list(APPEND fretypegl_all_LIBRARIES ${FREETYPE_LIBRARIES})
list(APPEND fretypegl_all_LIBRARIES ${GLFW_ALL_LIBRARIES})
set(FREETYPEGL_ALL_LIBRARIES ${fretypegl_all_LIBRARIES} CACHE STRING "${print_name} binary and dependencies")
#message("FREETYPEGL_ALL_LIBRARIES=${FREETYPEGL_ALL_LIBRARIES}\n")
