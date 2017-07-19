cmake_minimum_required(VERSION 3.1)

project(%{APPNAMELC})

############ ECM setup ###########
find_package(ECM 5.13.0 CONFIG REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})

include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)

########### Dependencies ###########

set(KF5_VERSION "5.13.0")
set(AKONADI_VERSION "5.0")
set(QT_REQUIRED_VERSION "5.3.0")

find_package(Qt5 ${QT_REQUIRED_VERSION} REQUIRED Core Network Gui)

find_package(KF5Config ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Akonadi ${AKONADI_MIN_VERSION} CONFIG REQUIRED)

find_program(XSLTPROC_EXECUTABLE xsltproc DOC "Path to xslt executable")

if(XSLTPROC_EXECUTABLE)
    # We depend on kdepimlibs, make sure it's found
    if(NOT DEFINED KF5Akonadi_DATA_DIR)
        find_package(KF5Akonadi REQUIRED)
    endif()

    # Macro to generate a D-Bus interface description from a KConfigXT file
    macro(kcfg_generate_dbus_interface _kcfg _name)
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_name}.xml
            COMMAND ${XSLTPROC_EXECUTABLE} --stringparam interfaceName ${_name}
                    ${KF5Akonadi_DATA_DIR}/kcfg2dbus.xsl
                    ${_kcfg}
                    > ${CMAKE_CURRENT_BINARY_DIR}/${_name}.xml
            DEPENDS ${KF5Akonadi_DATA_DIR}/kcfg2dbus.xsl
            ${_kcfg}
        )
    endmacro()
endif()

########### next target ###############

set(%{APPNAMELC}resource_SRCS
    %{APPNAMELC}resource.cpp
)

ecm_qt_declare_logging_category(%{APPNAMELC}resource_SRCS
    HEADER debug.h
    IDENTIFIER log_%{APPNAMELC}resource
    CATEGORY_NAME log_%{APPNAMELC}resource
)

kconfig_add_kcfg_files(%{APPNAMELC}resource_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/settings.kcfgc
)

kcfg_generate_dbus_interface(
    ${CMAKE_CURRENT_SOURCE_DIR}/%{APPNAMELC}resource.kcfg
    org.kde.Akonadi.%{APPNAME}.Settings
)

qt5_add_dbus_adaptor(%{APPNAMELC}resource_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/org.kde.Akonadi.%{APPNAME}.Settings.xml
    ${CMAKE_CURRENT_BINARY_DIR}/settings.h
    Settings
)


add_executable(akonadi_%{APPNAMELC}_resource ${%{APPNAMELC}resource_SRCS})
target_link_libraries(akonadi_%{APPNAMELC}_resource
    Qt5::DBus
    KF5::AkonadiAgentBase
    KF5::ConfigCore
)

install(TARGETS akonadi_%{APPNAMELC}_resource ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES %{APPNAMELC}resource.desktop
        DESTINATION "${KDE_INSTALL_DATAROOTDIR}/akonadi/agents"
)

########### summary ############

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
