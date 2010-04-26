
set(%{APPNAMELC}_SRCS %{APPNAMELC}plugin.cpp)

kde4_add_ui_files(%{APPNAMELC}_SRCS config.ui)

kde4_add_kcfg_files(%{APPNAMELC}_SRCS settings.kcfgc)

kde4_add_plugin(%{APPNAMELC} ${%{APPNAMELC}_SRCS})

target_link_libraries(%{APPNAMELC}  ${KDE4_KHTML_LIBS})


install(TARGETS %{APPNAMELC}  DESTINATION ${PLUGIN_INSTALL_DIR} )
install(FILES %{APPNAMELC}ui.rc %{APPNAMELC}.desktop  DESTINATION  ${DATA_INSTALL_DIR}/khtml/kpartplugins )
install(FILES %{APPNAMELC}ui.rc %{APPNAMELC}.desktop  DESTINATION  ${DATA_INSTALL_DIR}/kwebkitpart/kpartplugins )

