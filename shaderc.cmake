set(FOLK_SHADER_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/bgfx-full/bgfx/src")

function(folk_add_shader TARGET_NAME SRC_FILE TYPE BIN_FILE)
    shaderc( FILE "${SRC_FILE}"
             OUTPUT "${BIN_FILE}"
             ${TYPE}
             WINDOWS
             #PROFILE
             INCLUDES ${FOLK_SHADER_INCLUDES} 
             VERBOSE
             )
    add_custom_target(${TARGET_NAME} DEPENDS ${BIN_FILE})
endfunction()