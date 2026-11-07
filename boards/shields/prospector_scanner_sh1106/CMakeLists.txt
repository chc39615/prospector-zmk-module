if(CONFIG_SHIELD_PROSPECTOR_SCANNER_SH1106)
    target_sources_ifdef(CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM app PRIVATE src/custom_status_screen.c)
    target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
endif()