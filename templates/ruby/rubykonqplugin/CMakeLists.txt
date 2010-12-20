project(%{APPNAMELC})

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})



#add_subdirectory( doc )
add_subdirectory( src )
add_subdirectory( icons )
