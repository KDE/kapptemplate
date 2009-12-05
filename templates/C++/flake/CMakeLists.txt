PROJECT(%{APPNAME})

cmake_minimum_required(VERSION 2.6)

find_package(KDE4 REQUIRED)
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include(KDE4Defaults)
include(MacroLibrary)
include_directories(
    ${KDE4_INCLUDES}
)

set(%{APPNAMELC}_SRCS
		%{APPNAME}Shape.cpp
		%{APPNAME}Tool.cpp
		%{APPNAME}Widget.cpp
		%{APPNAME}Plugin.cpp
		%{APPNAME}ShapeFactory.cpp
		%{APPNAME}ToolFactory.cpp
)

kde4_add_plugin(%{APPNAMELC}shape ${%{APPNAMELC}_SRCS})

target_link_libraries(%{APPNAMELC}shape
    QtCore
    QtGui
    flake
    kostore
    ${KDE4_KDEUI_LIBS}
)

install(TARGETS %{APPNAMELC}shape DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES %{APPNAMELC}shape.desktop DESTINATION ${SERVICES_INSTALL_DIR})
