# CMakeList.txt : CMake project for FlukyEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)



find_package(OpenGL REQUIRED)

set(FLUKY_HEADERS 
				Engine.hpp
				Application.hpp
				Audio/AudioComponent.hpp
				Audio/AudioManager.hpp
				Platform/InputComponent.hpp
				Platform/Window.hpp
				Rendering/BoxComponent.hpp
				"World/Component.hpp"
				World/GameObject.hpp
				World/PlayerComponent.hpp
				World/Scene.hpp
				World/TransformComponent.hpp
				World/World.hpp
				)
set(FLUKY_SOURCES 
				Application.cpp
				Audio/AudioComponent.cpp
				Audio/AudioManager.cpp
				Platform/InputComponent.cpp
				Platform/Window.cpp
				Rendering/BoxComponent.cpp
				World/Scene.cpp
				World/TransformComponent.cpp
				World/World.cpp
				)
#file(GLOB_RECURSE Shaders  "${CMAKE_SOURCE_DIR}/Assets/Shaders/*")
#source_group("Shaders" FILES ${Shaders})

add_library(FlukyEngine STATIC ${FLUKY_SOURCES} ${FLUKY_HEADERS} FlukyEngine.hpp)
if (MSVC)
    target_compile_options(FlukyEngine PUBLIC /wd5033)
endif(MSVC)
target_include_directories(FlukyEngine PRIVATE ${THIRD_PARTY_INCLUDE_DIRECTORIES} FLUKY_INCLUDE_DIRECTORY)
target_link_libraries(FlukyEngine PRIVATE ${THIRD_PARTY_LIBRARIES})
set_property(TARGET FlukyEngine PROPERTY CXX_STANDARD 20)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${FLUKY_SOURCES} ${FLUKY_HEADERS})

