# CMake building script
#
# bRenderer framework by Benjamin Bürgisser 
#        [ https://github.com/bthdimension/bRenderer ]
#
# CMake script created by Enrique G. Paredes <egparedes@ifi.uzh.ch>
#                         VMMLab. University of Zürich. 2015

message(STATUS "---- Configuring bRenderer project ----")

# ---- Compilation ----
file(GLOB_RECURSE source_files *.cpp)
#message(STATUS "source_files set to ${source_files}")

add_library(${BRENDERER_PROJECT_NAME} SHARED ${source_files})
set_target_properties(${BRENDERER_PROJECT_NAME} PROPERTIES
                      OUTPUT_NAME ${BRENDERER_PROJECT_NAME})
#                      VERSION "${BRENDERER_VERSION_MAJOR}.${BRENDERER_VERSION_MINOR}"
#                      NO_SONAME)

get_cpp_options(cpp_flags c++11) 
#message(STATUS "cpp_flags set to ${cpp_flags}")
add_definitions(${cpp_flags})

# ---- Dependencies ----
# We do not need to find automatically built packages in 
# 'external-src' folder since the vars have been already set
# during the building
find_package(FreeImage REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(VMMLib REQUIRED)

include_directories(${BRENDERER_INCLUDE_DIR}
				    ${OPENGL_INCLUDE_DIR}
	                ${GLEW_INCLUDE_DIRS}
					${FREETYPEGL_INCLUDE_DIRS} 
	                ${GLFW_INCLUDE_DIR} 
	                ${FreeImage_INCLUDE_DIRS}
	                ${JSONCPP_INCLUDE_DIR} 
	                ${LIBOBJ_INCLUDE_DIR} 
	                ${VMMLIB_INCLUDE_DIRS})

target_link_libraries(${BRENDERER_PROJECT_NAME}
					  ${OPENGL_LIBRARIES}
	                  ${GLEW_LIBRARIES}
	                  ${FREETYPEGL_ALL_LIBRARIES} 
	                  ${GLFW_ALL_LIBRARIES}
	                  ${FreeImage_LIBRARIES}
	                  ${JSONCPP_LIBRARY}
	                  ${LIBOBJ_LIBRARY})

# ---- Post-build exports ----
# Export binary output and vars
get_target_property(lib_binary ${BRENDERER_PROJECT_NAME} LOCATION)

message(STATUS "Exporting ${BRENDERER_PROJECT_NAME} headers")
set(BRENDERER_INCLUDE_DIRS ${BRENDERER_INCLUDE_DIR})
list(APPEND BRENDERER_INCLUDE_DIRS
			${FREETYPEGL_INCLUDE_DIRS} 
		    ${GLFW_INCLUDE_DIR} 
		    ${JSONCPP_INCLUDE_DIR} 
		    ${LIBOBJ_INCLUDE_DIR} 
		    ${VMMLIB_INCLUDE_DIRS})
set(BRENDERER_INCLUDE_DIR ${BRENDERER_INCLUDE_DIR}
	CACHE STRING "${BRENDERER_PROJECT_NAME} library include path")
set(BRENDERER_INCLUDE_DIRS ${BRENDERER_INCLUDE_DIRS}
	CACHE STRING "All ${BRENDERER_PROJECT_NAME} header and dependencies paths")

message(STATUS "${BRENDERER_PROJECT_NAME} binary objects [${lib_binary}] will be exported after compilation")
set(BRENDERER_LIBRARY "${lib_binary}" 
	CACHE STRING "${BRENDERER_PROJECT_NAME} library binary")
set(BRENDERER_ALL_LIBRARIES ${BRENDERER_LIBRARY})
list(APPEND BRENDERER_ALL_LIBRARIES
			${FREETYPEGL_ALL_LIBRARIES} 
		    ${GLFW_ALL_LIBRARIES})
set(BRENDERER_ALL_LIBRARIES ${BRENDERER_ALL_LIBRARIES}
	CACHE STRING "All ${BRENDERER_PROJECT_NAME} library and dependencies binaries")

# ---- Installation ----
install(TARGETS ${BRENDERER_PROJECT_NAME}
        LIBRARY 
        DESTINATION ${BRENDERER_PROJECT_NAME}/${LIB_DIRNAME})
install(DIRECTORY ${BRENDERER_INCLUDE_DIR}
        DESTINATION ${BRENDERER_PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h" 
        		       PATTERN "*.hpp"
        		       PATTERN "*.hh")
install(DIRECTORY ${BRENDERER_DATA_DIR}
        DESTINATION ${BRENDERER_PROJECT_NAME}
        PATTERN "*"
        PATTERN ".DS*" EXCLUDE
        PATTERN "._*" EXCLUDE)

