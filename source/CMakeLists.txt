# CMakeList.txt : CMake project for FlukyEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)



find_package(OpenGL REQUIRED)

set(FLUKY_HEADERS 
				Platform/Window.hpp
				Platform/JoystickInput.hpp
				Platform/KeyCodes.hpp
				Rendering/BoxComponent.hpp
				Rendering/Text.hpp
				Audio/Audio.hpp
				World/World.hpp
				World/WorldTest.hpp
				World/TransformComponent.hpp
				World/RegistryHandler.hpp
				"World/Component.hpp"
				World/GameObject.hpp
				Application.hpp
				Engine.hpp
				)
set(FLUKY_SOURCES 
				Platform/Window.cpp
				Platform/JoystickInput.cpp
				Rendering/BoxComponent.cpp
				Rendering/Text.cpp
				Audio/Audio.cpp
				Application.cpp
				World/World.cpp
				World/WorldTest.cpp
				"World/Component.cpp"
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

