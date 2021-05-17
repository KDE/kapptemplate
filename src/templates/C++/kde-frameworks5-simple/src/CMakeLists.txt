add_executable(%{APPNAMELC})

target_sources(%{APPNAMELC} PRIVATE
    main.cpp
    %{APPNAMELC}window.cpp
)

ki18n_wrap_ui(%{APPNAMELC} %{APPNAMELC}.ui)

target_link_libraries(%{APPNAMELC}
    KF5::CoreAddons
    KF5::I18n
    Qt5::Widgets
)

install( TARGETS %{APPNAMELC} ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )
install( PROGRAMS org.example.%{APPNAMELC}.desktop DESTINATION ${KDE_INSTALL_APPDIR} )
install( FILES org.example.%{APPNAMELC}.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR} )
