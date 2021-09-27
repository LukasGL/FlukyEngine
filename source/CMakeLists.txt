# CMakeList.txt : CMake project for FlukyEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(OpenGL REQUIRED)
#find_package(glfw3 3.3 REQUIRED)

#target_link_libraries(FlukyEngine OpenGL::GL)
#target_link_binaries(FlukyEngine glfw)

set(FLUKY_HEADERS
				Graphics/window.h
)
set(FLUKY_SOURCES
				Graphics/window.cpp
)

#add_library(FlukyEngineLib STATIC ${FLUKY_HEADERS} ${FLUKY_SOURCES})

# Add source to this project's executable.
add_executable(FlukyEngineExe "Application.cpp" "Graphics/window.cpp" "Graphics/window.h")
#add_executable (FlukyEngine "Graphics/window.cpp" "Graphics/window.h")

#target_link_libraries(FlukyEngine PRIVATE ${FLUKY_SOURCES} ${FLUKY_HEADERS})
target_include_directories (FlukyEngineExe PRIVATE 
	"${THIRD_PARTY_INCLUDE_DIRECTORIES}"
)


# TODO: Add tests and install targets if needed.
target_link_libraries(FlukyEngineExe
	glfw
	OpenGL::GL
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${FLUKY_SOURCES} ${FLUKY_HEADERS})