
set_property( GLOBAL PROPERTY USE_FOLDERS ON )


function(MakeExample TARGETNAME FILENAME)
	add_executable(${TARGETNAME} ${FILENAME})
	#set_property(TARGET ${TARGETNAME} PROPERTY CXX_STANDARD 20)
	#set_property(TARGET ${TARGETNAME} PROPERTY FOLDER examples)
	target_include_directories(${TARGETNAME} PRIVATE ${FLUKY_INCLUDE_DIRECTORY} ${THIRD_PARTY_INCLUDE_DIRECTORIES})
	target_link_libraries(${TARGETNAME} PRIVATE FlukyEngine )

endfunction(MakeExample)

#MakeExample(ex_quad_pro ex_quad_pro.cpp)
MakeExample(ex_world ex_world.cpp)
MakeExample(ex_cube ex_cube.cpp)