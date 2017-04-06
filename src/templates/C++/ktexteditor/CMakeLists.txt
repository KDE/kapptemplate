cmake_minimum_required(VERSION 2.8.12)
project(%{APPNAMELC})

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(ECMAddTests)
include(FeatureSummary)

find_package(Qt5 REQUIRED COMPONENTS Test)
find_package(KF5 REQUIRED COMPONENTS CoreAddons TextEditor I18n Parts)

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
add_definitions(-DTRANSLATION_DOMAIN=\"%{APPNAMELC}\")

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(%{APPNAMELC}_SRCS
    %{APPNAMELC}.cpp
)

add_library(%{APPNAMELC} MODULE ${%{APPNAMELC}_SRCS})

target_link_libraries(%{APPNAMELC} KF5::TextEditor)

install(TARGETS %{APPNAMELC} DESTINATION ${PLUGIN_INSTALL_DIR}/ktexteditor)
