project(plasma-%{APPNAMELC})

# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )

# We add our source code here
set(%{APPNAMELC}_SRCS %{APPNAMELC}.cpp)

kde4_add_plugin(krunner_%{APPNAMELC} ${%{APPNAMELC}_SRCS})
target_link_libraries(krunner_%{APPNAMELC}
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})

install(TARGETS krunner_%{APPNAMELC}
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES %{APPNAMELC}.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})

