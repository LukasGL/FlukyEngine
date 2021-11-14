# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("FlukyEngine")

# first we can indicate the documentation build as an option and set it to ON by default
# option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

#find_package(OpenGL REQUIRED)
set(THIRD_PARTY_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glfw-3.3.4/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glad/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glm-0.9.9.8"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/imgui"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/bgfx-full/bgfx/examples/common"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/openal-soft/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/dr_wav"
                                    "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/entt/src")

set(FLUKY_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source")

if(MSVC)
	set(THIRD_PARTY_LIBRARIES OpenGL::GL glfw glad ImGui bgfx bx bimg dear-imgui meshoptimizer OpenAL dr_wav)
else()
	set(THIRD_PARTY_LIBRARIES OpenGL::GL glfw glad ImGui bgfx bx bimg dear-imgui meshoptimizer stdc++fs OpenAL dr_wav)
endif(MSVC)

# Include sub-projects.
add_subdirectory("examples-fluky")
add_subdirectory("thirdParty")
add_subdirectory("source")

