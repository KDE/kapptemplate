find_package(KDE4 REQUIRED)

set(UI_PREFS_BASE ${CMAKE_CURRENT_SOURCE_DIR}/prefs_base.ui)
set(UI_%{APPNAMEUC}_VIEW_BASE ${CMAKE_CURRENT_SOURCE_DIR}/%{APPNAMELC}view_base.ui)
set(SETTINGS_KCFGC ${CMAKE_CURRENT_SOURCE_DIR}/settings.kcfgc)
set(%{APPNAMEUC}_KCFG ${CMAKE_CURRENT_SOURCE_DIR}/%{APPNAMELC}.kcfg)

find_program(RBUIC4 rbuic4 PATHS ${BIN_INSTALL_DIR})
if(RBUIC4)
    find_program(RBKCONFIG_COMPILER4 rbkconfig_compiler4 PATHS ${BIN_INSTALL_DIR})
    if(RBKCONFIG_COMPILER4)
        add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/settings.rb COMMAND ${RBKCONFIG_COMPILER4} -d ${CMAKE_CURRENT_BINARY_DIR} ${%{APPNAMEUC}_KCFG} ${SETTINGS_KCFGC} COMMENT "Generating settings.rb")
        add_custom_target(settings ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/settings.rb)

        add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ui_prefs_base.rb COMMAND ${RBUIC4} -tr KDE::tr2i18n ${UI_PREFS_BASE} -o ${CMAKE_CURRENT_BINARY_DIR}/ui_prefs_base.rb COMMENT "Generating ui_prefs_base.rb")
        add_custom_target(prefs_base ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/ui_prefs_base.rb)
        add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ui_%{APPNAMELC}view_base.rb COMMAND ${RBUIC4} -tr KDE::tr2i18n ${UI_%{APPNAMEUC}_VIEW_BASE} -o ${CMAKE_CURRENT_BINARY_DIR}/ui_%{APPNAMELC}view_base.rb COMMENT "Generating ui_%{APPNAMELC}view_base.rb")
        add_custom_target(%{APPNAMELC}view_base ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/ui_%{APPNAMELC}view_base.rb)

        install( PROGRAMS %{APPNAMELC}.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
        install( FILES %{APPNAMELC}ui.rc  DESTINATION  ${DATA_INSTALL_DIR}/%{APPNAMELC} )

        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ui_prefs_base.rb DESTINATION ${DATA_INSTALL_DIR}/%{APPNAMELC})
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ui_%{APPNAMELC}view_base.rb DESTINATION ${DATA_INSTALL_DIR}/%{APPNAMELC})
        install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/%{APPNAMELC}.rb DESTINATION ${DATA_INSTALL_DIR}/%{APPNAMELC})
        install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.rb DESTINATION ${DATA_INSTALL_DIR}/%{APPNAMELC})
        install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/%{APPNAMELC}view.rb DESTINATION ${DATA_INSTALL_DIR}/%{APPNAMELC})
        install( FILES %{APPNAMELC}.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
    else(RBKCONFIG_COMPILER4)
        message(STATUS "rbkconfig_compiler4 not found, settings.rb will not created")
    endif(RBKCONFIG_COMPILER4)
else(RBUIC4)
    message(STATUS "rbuic4 not found, %{APPNAMELC} will not created")
endif(RBUIC4)


