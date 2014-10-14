project(ktexteditor_%{APPNAMELC})

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(ktexteditor_%{APPNAMELC}_SRCS %{APPNAMELC}plugin.cpp)

kde4_add_plugin(ktexteditor_%{APPNAMELC} ${ktexteditor_%{APPNAMELC}_SRCS})

target_link_libraries(ktexteditor_%{APPNAMELC} ${KDE4_KDEUI_LIBS} ${KDE4_KTEXTEDITOR_LIBS})

install(TARGETS ktexteditor_%{APPNAMELC} DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES %{APPNAMELC}ui.rc DESTINATION ${DATA_INSTALL_DIR}/ktexteditor_%{APPNAMELC})

install(FILES ktexteditor_%{APPNAMELC}.desktop DESTINATION ${SERVICES_INSTALL_DIR})
 
