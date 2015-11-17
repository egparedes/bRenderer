# CMake building script
#
# GLFW frameowrk [ http://www.glfw.org/ ]
#
# CMake script created by Enrique G. Paredes <egparedes@ifi.uzh.ch>
#                         VMMLab. University of Zürich. 2015

set(lib_name glfw)
set(print_name GLFW)

message(STATUS "Building ${print_name} library [${lib_name}]")
set(src_sub_dir glfw-3.1.1)
set(include_output_dir "${BRENDERER_EXPORT_DIR}/${lib_name}/${INCLUDE_DIRNAME}")
set(lib_output_dir "${BRENDERER_EXPORT_DIR}/${lib_name}/${LIB_DIRNAME}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BRENDERER_EXPORT_DIR}/${lib_name}/${LIB_DIRNAME}")

# ---- Compilation ----
add_subdirectory(${src_sub_dir})

# ---- Post-build exports ----
# Export binary output and vars
get_target_property(lib_output ${lib_name} LOCATION)
get_filename_component(lib_binary ${lib_output} NAME)

message(STATUS "Exporting ${print_name} headers")
set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/${src_sub_dir}/include/")
copy_file_hierarchy(${src_dir} ${include_output_dir} *.h)
set(GLFW_INCLUDE_DIR ${include_output_dir}
	CACHE STRING "${print_name} library include path")

message(STATUS "${print_name} binary objects [${lib_binary}] will be exported after compilation")
set(glfw_all_LIBRARIES ${GLFW_LIBRARIES})
list(APPEND glfw_all_LIBRARIES "${lib_output_dir}/${lib_binary}")
set(GLFW_ALL_LIBRARIES ${glfw_all_LIBRARIES}
	CACHE STRING "${print_name} binary and dependencies")
#message("GLFW_ALL_LIBRARIES=${GLFW_ALL_LIBRARIES}\n")
