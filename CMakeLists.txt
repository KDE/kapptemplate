cmake_minimum_required(VERSION 3.0)

project(kapptemplate)

set(QT_MIN_VERSION "5.9.0")
set(KF_MIN_VERSION "5.53.0")

find_package(ECM ${KF_MIN_VERSION} NO_MODULE REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(ECMAddTests)
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

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

add_subdirectory(doc)
add_subdirectory(icons)
add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
