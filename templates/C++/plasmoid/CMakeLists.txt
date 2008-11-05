# Project Needs a name ofcourse
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
 
# Now make sure all files get to the right place
kde4_add_plugin(plasma_applet_%{APPNAMELC} ${%{APPNAMELC}_SRCS})
target_link_libraries(plasma_applet_%{APPNAMELC} 
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})
 
install(TARGETS plasma_applet_%{APPNAMELC}
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-applet-%{APPNAMELC}.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
