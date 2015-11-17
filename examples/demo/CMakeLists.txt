# CMake building script
#
# Demo project for bRenderer framework created by Benjamin Bürgisser 
#      [ https://github.com/bthdimension/bRenderer ]
#
# CMake script created by Enrique G. Paredes <egparedes@ifi.uzh.ch>
#                         VMMLab. University of Zürich. 2015

project(demo)
message(STATUS "---- Configuring '${PROJECT_NAME}' example ----")

# ---- Compilation ----
file(GLOB_RECURSE source_files *.cpp)
#message(STATUS "source_files set to ${source_files}")

add_executable(${PROJECT_NAME} ${source_files})

get_cpp_options(cpp_flags c++11) 
#message(STATUS "cpp_flags set to ${cpp_flags}")
add_definitions(${cpp_flags})

set_target_properties(${PROJECT_NAME} 
	PROPERTIES INSTALL_RPATH "$ORIGIN/:$ORIGIN/lib:$ORIGIN/../lib")

# ---- Dependencies ----
# bRenderer package already includes all the required 
# headers and libraries
find_package(bRenderer REQUIRED)

include_directories(${BRENDERER_INCLUDE_DIRS})

#message("BRENDERER_ALL_LIBRARIES=${BRENDERER_ALL_LIBRARIES}")
target_link_libraries(${PROJECT_NAME} ${BRENDERER_ALL_LIBRARIES})

# ---- Installation ----
install(TARGETS ${PROJECT_NAME} 
		RUNTIME 
		DESTINATION ${PROJECT_NAME})
install(FILES ${BRENDERER_LIBRARY}
        DESTINATION ${PROJECT_NAME}/${LIB_DIRNAME})
install(DIRECTORY ${DATA_DIRNAME}
        DESTINATION ${PROJECT_NAME}
        PATTERN "*"
        PATTERN ".DS*" EXCLUDE
        PATTERN "._*" EXCLUDE)
