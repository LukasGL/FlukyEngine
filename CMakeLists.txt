# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("FlukyEngine")

#find_package(OpenGL REQUIRED)
#set(THIRD_PARTY_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glfw-3.3.2/include")

#set(FLUKY_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FlukyEngine")

# Include sub-projects.
add_subdirectory("FlukyEngine")
