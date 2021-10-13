find_package(OpenGL REQUIRED)

function(MakeExample TARGETNAME FILENAME)
	add_executable(${TARGETNAME} ${FILENAME})
	#set_property(TARGET ${TARGETNAME} PROPERTY CXX_STANDARD 20)
	#set_property(TARGET ${TARGETNAME} PROPERTY FOLDER examples)
	target_include_directories(${TARGETNAME} PRIVATE ${THIRD_PARTY_INCLUDE_DIRECTORIES})
	target_link_libraries(${TARGETNAME} PRIVATE ${THIRD_PARTY_LIBRARIES} )

endfunction(MakeExample)

#MakeExample(ex_quad_pro ex_quad_pro.cpp)
MakeExample(ex_imgui ex_imgui.cpp)
MakeExample(ex_bgfx ex_bgfx.cpp)