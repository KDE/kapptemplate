set( %{APPNAMELC}_SRCS
    main.cpp
    %{APPNAMELC}.cpp
    %{APPNAMELC}view.cpp
)

kconfig_add_kcfg_files(%{APPNAMELC}_SRCS %{APPNAME}Settings.kcfgc)
ki18n_wrap_ui(%{APPNAMELC}_SRCS %{APPNAMELC}ViewBase.ui settingsBase.ui)

add_executable( %{APPNAMELC} ${%{APPNAMELC}_SRCS} )

target_link_libraries( %{APPNAMELC}
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::ConfigWidgets
)

install( TARGETS %{APPNAMELC} ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( PROGRAMS %{APPNAMELC}.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES %{APPNAMELC}ui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/%{APPNAMELC} )
