set( %{APPNAMELC}_SRCS
    main.cpp
    %{APPNAMELC}.cpp
)

ki18n_wrap_ui(%{APPNAMELC}_SRCS %{APPNAMELC}.ui)

add_executable( %{APPNAMELC} ${%{APPNAMELC}_SRCS} )

target_link_libraries( %{APPNAMELC}
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
)

install( TARGETS %{APPNAMELC} ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( PROGRAMS %{APPNAMELC}.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
