cmake_minimum_required(VERSION 2.8.12)
project(kapptemplate)

find_package(ECM 5.17.0 NO_MODULE REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(ECMInstallIcons)
include(ECMAddTests)
include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(KDEPackageAppTemplates)
include(FeatureSummary)

find_package(Qt5 REQUIRED COMPONENTS Test)
find_package(KF5 REQUIRED COMPONENTS CoreAddons ConfigWidgets Completion Archive KIO I18n DocTools)

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

add_subdirectory(doc)
add_subdirectory(icons)
add_subdirectory(src)
add_subdirectory(tests)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
