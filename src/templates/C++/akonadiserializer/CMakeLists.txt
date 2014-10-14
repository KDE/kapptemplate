project(%{APPNAMELC})

# search packages used by KDE
find_package (KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalAddSubdirectory)
include(CheckIncludeFiles)
find_package (KdepimLibs REQUIRED)

if(WIN32)
    set(LIB_INSTALL_DIR ${LIB_INSTALL_DIR}
                        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
                        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
                        ARCHIVE DESTINATION ${LIB_INSTALL_DIR} )
endif(WIN32)

include_directories(
    ${KDE4_INCLUDES}
    ${KDEPIMLIBS_INCLUDE_DIRS}
)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}" )


########### next target ###############

set( akonadi_serializer_%{APPNAMELC}_SRCS
  akonadi_serializer_%{APPNAMELC}.cpp
)

kde4_add_plugin(akonadi_serializer_%{APPNAMELC} ${akonadi_serializer_%{APPNAMELC}_SRCS})

target_link_libraries(akonadi_serializer_%{APPNAMELC} ${KDE4_AKONADI_LIBS} ${QT_QTCORE_LIBRARY} ${KDE4_KDECORE_LIBS})

install(TARGETS akonadi_serializer_%{APPNAMELC} DESTINATION ${PLUGIN_INSTALL_DIR})

########### install files ###############

install( FILES
  akonadi_serializer_%{APPNAMELC}.desktop
  DESTINATION ${DATA_INSTALL_DIR}/akonadi/plugins/serializer)
