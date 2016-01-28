cmake_minimum_required(VERSION 3.1)

project(%{APPNAMELC})

############ ECM setup ###########
find_package(ECM 5.13.0 CONFIG REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})

include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

########### Dependencies ###########

set(KF5_VERSION "5.13.0")
set(AKONADI_VERSION "5.0")
set(QT_REQUIRED_VERSION "5.3.0")

find_package(Qt5 ${QT_REQUIRED_VERSION} REQUIRED Core Network Gui)

find_package(KF5Config ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Akonadi ${AKONADI_MIN_VERSION} CONFIG REQUIRED)

########### next target ###############

set( akonadi_serializer_%{APPNAMELC}_SRCS
  akonadi_serializer_%{APPNAMELC}.cpp
)

add_library(akonadi_serializer_%{APPNAMELC} MODULE ${akonadi_serializer_%{APPNAMELC}_SRCS})
target_link_libraries(akonadi_serializer_%{APPNAMELC}
    KF5::AkonadiCore
)

install(TARGETS akonadi_serializer_%{APPNAMELC}
        DESTINATION ${KDE_INSTALL_PLUGINDIR})

########### install files ###############

install(FILES akonadi_serializer_%{APPNAMELC}.desktop
        DESTINATION ${KDE_INSTALL_DATADIR}/akonadi/plugins/serializer
)
