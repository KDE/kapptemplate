add_executable(%{APPNAMELC})

target_sources(%{APPNAMELC} PRIVATE
    main.cpp
    %{APPNAMELC}window.cpp
    %{APPNAMELC}view.cpp
)

ecm_qt_declare_logging_category(%{APPNAMELC}
    HEADER %{APPNAMELC}debug.h
    IDENTIFIER %{APPNAMEUC}
    CATEGORY_NAME "%{APPNAMELC}"
)
kconfig_add_kcfg_files(%{APPNAMELC} %{APPNAME}Settings.kcfgc)
ki18n_wrap_ui(%{APPNAMELC}
    %{APPNAMELC}view.ui
    settings.ui
)

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
