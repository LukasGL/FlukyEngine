# CMakeList.txt : CMake project for FlukyEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

#find_package(OpenGL REQUIRED)
#find_package(glfw3 3.3 REQUIRED)

#target_link_libraries(FlukyEngine OpenGL::GL)
#target_link_binaries(FlukyEngine glfw)

# Add source to this project's executable.
add_executable (FlukyEngine "FlukyEngine.cpp")


# TODO: Add tests and install targets if needed.
