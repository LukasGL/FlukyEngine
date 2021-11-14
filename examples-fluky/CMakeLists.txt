


function(MakeExample TARGETNAME FILENAME)
	add_executable(${TARGETNAME} ${FILENAME})
	set_property(TARGET ${TARGETNAME} PROPERTY CXX_STANDARD 20)
	#set_property(TARGET ${TARGETNAME} PROPERTY FOLDER examples)
	target_include_directories(${TARGETNAME} PRIVATE ${FLUKY_INCLUDE_DIRECTORY} ${THIRD_PARTY_INCLUDE_DIRECTORIES})
	target_link_libraries(${TARGETNAME} PRIVATE FlukyEngine )

endfunction(MakeExample)

#MakeExample(ex_quad_pro ex_quad_pro.cpp)
#MakeExample(ex_world ex_world.cpp)
#MakeExample(ex_cube ex_cube.cpp)
#MakeExample(ex_audio ex_audio.cpp)
#MakeExample(ex_text ex_text.cpp)
MakeExample(ex_components ex_components.cpp)

#add_custom_command(
 #       TARGET ex_world POST_BUILD
  #      COMMAND ${CMAKE_COMMAND} -E copy
   #             ${CMAKE_SOURCE_DIR}/examples-fluky/demo/demo.wav
    #            ${CMAKE_CURRENT_BINARY_DIR}/demo.wav)