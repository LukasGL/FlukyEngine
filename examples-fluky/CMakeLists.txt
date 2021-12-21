#set(SHADER_DIR ${CMAKE_CURRENT_BINARY_DIR}/../thirdParty/bgfx-full/shaders)

#folk_add_shader(default_vert_shader "shaders/vs_cubes.sc" VERTEX "${SHADER_DIR}/vs_cubes.bin")
#folk_add_shader(default_frag_shader "shaders/fs_cubes.sc" FRAGMENT "${SHADER_DIR}/fs_cubes.bin")

#add_custom_target(default_shaders)
#add_dependencies(default_shaders default_vert_shader default_frag_shader)

#add_custom_target(fluky_examples ALL)
#add_dependencies(fluky_examples default_shaders)


function(MakeExample TARGETNAME FILENAME)
	add_executable(${TARGETNAME} ${FILENAME})
	set_property(TARGET ${TARGETNAME} PROPERTY CXX_STANDARD 20)
	#set_property(TARGET ${TARGETNAME} PROPERTY FOLDER examples)
	target_include_directories(${TARGETNAME} PRIVATE ${FLUKY_INCLUDE_DIRECTORY} ${THIRD_PARTY_INCLUDE_DIRECTORIES})
	target_link_libraries(${TARGETNAME} PRIVATE FlukyEngine )
    #add_dependencies(${TARGETNAME} fluky_examples)
endfunction(MakeExample)

MakeExample(ex_audio ex_audio.cpp)
MakeExample(ex_multiaudio ex_multiaudio.cpp)
MakeExample(ex_components ex_components.cpp)
MakeExample(ex_players ex_players.cpp)
MakeExample(ex_deletegobject ex_deletegobject.cpp)
MakeExample(ex_camera ex_camera.cpp)
MakeExample(ex_cameratest ex_cameratest.cpp)
MakeExample(ex_physics ex_physics.cpp)
MakeExample(ex_triggerphysics ex_triggerphysics.cpp)
MakeExample(ex_gameLvl1 ex_gameLvl1.cpp)
MakeExample(ex_gamelvl ex_gamelvl.cpp)

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
configure_files(${CMAKE_SOURCE_DIR}/examples-fluky/textures ${CMAKE_CURRENT_BINARY_DIR}/../thirdParty/bgfx-full/textures)
#file(GLOB shaderDir RELATIVE ${CMAKE_SOURCE_DIR}/examples-fluky/shaders/ ${srcDir}/*)
foreach (DIR ${CMAKE_SOURCE_DIR}/examples-fluky/shaders/*)
    get_filename_component(dir_name ${DIR} NAME)
    configure_files(${DIR} ${CMAKE_CURRENT_BINARY_DIR}/shaders/${dir_name})
endforeach(DIR)




#foreach(FNAME "${CMAKE_SOURCE_DIR}/examples-fluky/demo"/*)
 #   set(SRC "${CMAKE_SOURCE_DIR}/examples-fluky/demo/${FNAME}")
  #  set(DST "${CMAKE_CURRENT_BINARY_DIR}/${FNAME}")
	#add_custom_command(
     #   TARGET ex_audio POST_BUILD
      #  COMMAND ${CMAKE_COMMAND} -E copy
       #         ${SRC}
        #        ${DST})
#endforeach(FILENAME)