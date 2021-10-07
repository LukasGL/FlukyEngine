# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("FlukyEngine")

set(BGFX_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/bgfx-full/bgfx/include/bgfx"
							 "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/bgfx-full/bgfx/examples/common"
							 "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/bgfx-full/bimg/include"
							 "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/bgfx-full/bx/include")


#find_package(OpenGL REQUIRED)
set(THIRD_PARTY_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glfw-3.3.4/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glad/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glm-0.9.9.8"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/imgui"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/bgfx-full/bgfx/examples/common"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/Easy3D")

#set(FLUKY_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FlukyEngine")

# Include sub-projects.
add_subdirectory("thirdParty")
add_subdirectory("source")

