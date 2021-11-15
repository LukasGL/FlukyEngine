


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
MakeExample(ex_audio ex_audio.cpp)
MakeExample(ex_multiaudio ex_multiaudio.cpp)
#MakeExample(ex_text ex_text.cpp)
MakeExample(ex_components ex_components.cpp)
MakeExample(ex_players ex_players.cpp)

macro(configure_files srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    COPYONLY)
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(configure_files)

configure_files(${CMAKE_SOURCE_DIR}/examples-fluky/demo ${CMAKE_CURRENT_BINARY_DIR})

#foreach(FNAME "${CMAKE_SOURCE_DIR}/examples-fluky/demo"/*)
 #   set(SRC "${CMAKE_SOURCE_DIR}/examples-fluky/demo/${FNAME}")
  #  set(DST "${CMAKE_CURRENT_BINARY_DIR}/${FNAME}")
	#add_custom_command(
     #   TARGET ex_audio POST_BUILD
      #  COMMAND ${CMAKE_COMMAND} -E copy
       #         ${SRC}
        #        ${DST})
#endforeach(FILENAME)