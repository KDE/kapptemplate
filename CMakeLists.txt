cmake_minimum_required(VERSION 3.16)

# Release Service version, managed by release script
set (RELEASE_SERVICE_VERSION_MAJOR "22")
set (RELEASE_SERVICE_VERSION_MINOR "04")
set (RELEASE_SERVICE_VERSION_MICRO "1")
set (RELEASE_SERVICE_COMPACT_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}${RELEASE_SERVICE_VERSION_MINOR}${RELEASE_SERVICE_VERSION_MICRO}")

# Bump KAPPTEMPLATE_BASE_VERSION once new features are added
set(KAPPTEMPLATE_BASE_VERSION "0.1")
set(KAPPTEMPLATE_VERSION "${KAPPTEMPLATE_BASE_VERSION}.${RELEASE_SERVICE_COMPACT_VERSION}")

project(kapptemplate VERSION ${KAPPTEMPLATE_VERSION})

set(QT_MIN_VERSION "5.15.0")
set(KF_MIN_VERSION "5.85.0")

find_package(ECM ${KF_MIN_VERSION} NO_MODULE REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(ECMInstallIcons)
include(ECMSetupVersion)
include(ECMAddTests)
include(ECMQtDeclareLoggingCategory)
include(KDEPackageAppTemplates)
include(FeatureSummary)

if (BUILD_TESTING)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Test)
endif()

find_package(KF5 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons
    ConfigWidgets
    Completion
    Archive
    KIO
    I18n
    DocTools
    # NewStuff
)

add_definitions(
    -DQT_DISABLE_DEPRECATED_BEFORE=0x050F00
    -DQT_DEPRECATED_WARNINGS_SINCE=0x060000
    -DKF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x055500
    -DKF_DEPRECATED_WARNINGS_SINCE=0x060000
)
# aded by KDE_COMPILERSETTINGS_LEVEL 5.85
remove_definitions(
    -DQT_NO_CAST_FROM_ASCII
)

add_subdirectory(doc)
add_subdirectory(icons)
add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

ki18n_install(po)
kdoctools_install(po)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
