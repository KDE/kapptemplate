set(%{APPNAMELC}_SRCS
   main.cpp
   %{APPNAMELC}.cpp
 )

kde4_add_executable(%{APPNAMELC} ${%{APPNAMELC}_SRCS})

target_link_libraries(%{APPNAMELC} ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS})

########### install files ###############
install(TARGETS %{APPNAMELC} ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( PROGRAMS %{APPNAMELC}.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES %{APPNAMELC}_shell.rc  DESTINATION  ${DATA_INSTALL_DIR}/%{APPNAMELC} )


#########################################################################
# KPART SECTION
#########################################################################
#kde_module_LTLIBRARIES = lib%{APPNAMELC}part.la
set(%{APPNAMELC}_PART_SRCS
   %{APPNAMELC}_part.cpp
 )

kde4_add_plugin(%{APPNAMELC}part WITH_PREFIX ${%{APPNAMELC}_PART_SRCS})

target_link_libraries(%{APPNAMELC}part ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} )

install( PROGRAMS %{APPNAMELC}_part.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES %{APPNAMELC}_part.rc  DESTINATION  ${DATA_INSTALL_DIR}/%{APPNAMELC}part )

install(TARGETS %{APPNAMELC}part  DESTINATION ${PLUGIN_INSTALL_DIR} )
