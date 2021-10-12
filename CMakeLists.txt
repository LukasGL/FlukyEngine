# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("FlukyEngine")


#find_package(OpenGL REQUIRED)
set(THIRD_PARTY_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glfw-3.3.4/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glad/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glm-0.9.9.8"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/imgui"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/bgfx-full/bgfx/examples/common"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/Easy3D"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/openal-soft/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/dr_wav")

set(FLUKY_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source")

if(MSVC)
	set(THIRD_PARTY_LIBRARIES OpenGL::GL glfw glad ImGui bgfx bx bimg dear-imgui meshoptimizer easy3d::core easy3d::viewer OpenAL dr_wav)
else()
	set(THIRD_PARTY_LIBRARIES OpenGL::GL glfw glad ImGui bgfx bx bimg dear-imgui meshoptimizer easy3d::core easy3d::viewer stdc++fs OpenAL dr_wav)
endif(MSVC)

# Include sub-projects.
add_subdirectory("examples")
add_subdirectory("examples-fluky")
add_subdirectory("thirdParty")
add_subdirectory("source")

