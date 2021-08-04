cmake_minimum_required(VERSION 3.16)

# Release Service version, managed by release script
set (RELEASE_SERVICE_VERSION_MAJOR "21")
set (RELEASE_SERVICE_VERSION_MINOR "08")
set (RELEASE_SERVICE_VERSION_MICRO "0")
set (RELEASE_SERVICE_COMPACT_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}${RELEASE_SERVICE_VERSION_MINOR}${RELEASE_SERVICE_VERSION_MICRO}")

# Bump KAPPTEMPLATE_BASE_VERSION once new features are added
set(KAPPTEMPLATE_BASE_VERSION "0.1")
set(KAPPTEMPLATE_VERSION "${KAPPTEMPLATE_BASE_VERSION}.${RELEASE_SERVICE_COMPACT_VERSION}")

project(kapptemplate VERSION ${KAPPTEMPLATE_VERSION})

set(QT_MIN_VERSION "5.15.0")
set(KF_MIN_VERSION "5.83.0")

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
    -DQT_DEPRECATED_WARNINGS
    -DQT_DISABLE_DEPRECATED_BEFORE=0x050F00
    -DQT_USE_QSTRINGBUILDER
    -DQT_NO_CAST_TO_ASCII
#     -DQT_NO_CAST_FROM_ASCII
    -DQT_NO_CAST_FROM_BYTEARRAY
    -DQT_STRICT_ITERATORS
    -DQT_NO_URL_CAST_FROM_STRING
    -DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT
    -DQT_NO_FOREACH
    -DQT_NO_KEYWORDS
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
