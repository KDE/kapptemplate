find_program(RBUIC4 rbuic4 PATHS ${BIN_INSTALL_DIR})
if(RBUIC4)
	find_program(RBKCONFIG_COMPILER4 rbkconfig_compiler4 PATHS ${BIN_INSTALL_DIR})
	if(RBKCONFIG_COMPILER4)
		add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/settings.rb COMMAND ${RBKCONFIG_COMPILER4} -d ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/%{APPNAMELC}.kcfg ${CMAKE_CURRENT_SOURCE_DIR}/settings.kcfgc  COMMENT "Generating settings.rb")
		add_custom_target(settings ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/settings.rb)
		
		add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ui_config.rb COMMAND ${RBUIC4} -tr KDE::tr2i18n ${CMAKE_CURRENT_SOURCE_DIR}/config.ui -o ${CMAKE_CURRENT_BINARY_DIR}/ui_config.rb COMMENT "Generating ui_config.rb")
		add_custom_target(config ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/ui_config.rb)
		
		set(%{APPNAMEUC}_FILES ${CMAKE_CURRENT_BINARY_DIR}/settings.rb ${CMAKE_CURRENT_BINARY_DIR}/ui_config.rb)

		install(PROGRAMS %{APPNAME}.rb DESTINATION ${DATA_INSTALL_DIR}/%{APPNAME})
		install(FILES ${%{APPNAMEUC}_FILES} DESTINATION ${DATA_INSTALL_DIR}/%{APPNAME} )
		install(FILES %{APPNAMELC}.rc %{APPNAMELC}.desktop DESTINATION ${DATA_INSTALL_DIR}/khtml/kpartplugins)
		
	else(RBKCONFIG_COMPILER4)
		message(STATUS "rbkconfig_compiler4 not found, %{APPNAMELC} will not be created")
	endif(RBKCONFIG_COMPILER4)
else(RBUIC4)
	message(STATUS "rbuic4 not found, %{APPNAMELC} will not be created")
endif(RBUIC4)
