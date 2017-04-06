set(%{APPNAMELC}_SRCS
   main.cpp
   %{APPNAMELC}.cpp
)

add_executable(%{APPNAMELC} ${%{APPNAMELC}_SRCS})

target_link_libraries(%{APPNAMELC}
    KF5::I18n
    KF5::Parts
    KF5::DBusAddons
    KF5::Crash
)

########### install files ###############
install(TARGETS %{APPNAMELC} ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS %{APPNAMELC}.desktop  DESTINATION  ${KDE_INSTALL_APPDIR})
install(FILES %{APPNAMELC}_shell.rc  DESTINATION  ${KDE_INSTALL_KXMLGUI5DIR}/%{APPNAMELC} )


#########################################################################
# KPART SECTION
#########################################################################
set(%{APPNAMELC}_PART_SRCS
   %{APPNAMELC}_part.cpp
 )

add_library(%{APPNAMELC}part MODULE ${%{APPNAMELC}_PART_SRCS})

target_link_libraries(%{APPNAMELC}part
    KF5::I18n
    KF5::Parts
)

install(PROGRAMS %{APPNAMELC}_part.desktop  DESTINATION ${KDE_INSTALL_APPDIR} )
install(FILES %{APPNAMELC}_part.rc  DESTINATION  ${KDE_INSTALL_KXMLGUI5DIR}/%{APPNAMELC}part )

install(TARGETS %{APPNAMELC}part  DESTINATION ${KDE_INSTALL_PLUGINDIR})
