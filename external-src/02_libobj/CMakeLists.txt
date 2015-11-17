# CMake building script
#
# Libobj library by Ares Lagae [ http://people.cs.kuleuven.be/~ares.lagae/libobj/ ]
#
# CMake script created by Enrique G. Paredes <egparedes@ifi.uzh.ch>
#                         VMMLab. University of Zürich. 2015

set(lib_name obj)
set(print_name Libobj)

message(STATUS "Building ${print_name} library [${lib_name}]")
set(include_output_dir "${BRENDERER_EXPORT_DIR}/${lib_name}/${INCLUDE_DIRNAME}")
set(lib_output_dir "${BRENDERER_EXPORT_DIR}/${lib_name}/${LIB_DIRNAME}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BRENDERER_EXPORT_DIR}/${lib_name}/${LIB_DIRNAME}")

# ---- Compilation ----
file(GLOB_RECURSE source_files *.cpp *.c)
#message(STATUS "source_files set to ${source_files}")

include_directories(${include_output_dir})
add_library(${lib_name} ${source_files})

get_cpp_options(cpp_flags c++11 fPIC) 
#message(STATUS "cpp_flags set to ${cpp_flags}")
add_definitions(${cpp_flags})

# ---- Post-build exports ----
# Export binary output and vars
get_target_property(lib_output ${lib_name} LOCATION)
get_filename_component(lib_binary ${lib_output} NAME)

message(STATUS "Exporting ${print_name} headers")
set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}")
copy_file_hierarchy(${src_dir} ${include_output_dir} *.h *.hpp)
set(LIBOBJ_INCLUDE_DIR "${include_output_dir}" CACHE STRING "${print_name} library include path")

message(STATUS "${print_name} binary objects [${lib_binary}] will be exported after compilation")
set(LIBOBJ_LIBRARY "${lib_output_dir}/${lib_binary}" CACHE STRING "${print_name} library binary")
