set(%{APPNAMELC}_SRCS
    main.cpp
    %{APPNAMELC}window.cpp
    %{APPNAMELC}view.cpp
)

ecm_qt_declare_logging_category(%{APPNAMELC}_SRCS
    HEADER %{APPNAMELC}debug.h
    IDENTIFIER %{APPNAMEUC}
    CATEGORY_NAME "%{APPNAMELC}"
)
kconfig_add_kcfg_files(%{APPNAMELC}_SRCS %{APPNAME}Settings.kcfgc)
ki18n_wrap_ui(%{APPNAMELC}_SRCS
    %{APPNAMELC}ViewBase.ui
    settingsBase.ui
)

add_executable(%{APPNAMELC} ${%{APPNAMELC}_SRCS})

target_link_libraries(%{APPNAMELC}
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::ConfigWidgets
    KF5::DBusAddons
    KF5::Crash
    Qt5::Widgets
)

install(TARGETS %{APPNAMELC} ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.example.%{APPNAMELC}.desktop  DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.example.%{APPNAMELC}.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES %{APPNAMELC}ui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/%{APPNAMELC})
