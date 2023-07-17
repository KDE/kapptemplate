cmake_minimum_required(VERSION 3.16)

# Release Service version, managed by release script
set (RELEASE_SERVICE_VERSION_MAJOR "23")
set (RELEASE_SERVICE_VERSION_MINOR "07")
set (RELEASE_SERVICE_VERSION_MICRO "80")
set (RELEASE_SERVICE_COMPACT_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}${RELEASE_SERVICE_VERSION_MINOR}${RELEASE_SERVICE_VERSION_MICRO}")

# Bump KAPPTEMPLATE_BASE_VERSION once new features are added
set(KAPPTEMPLATE_BASE_VERSION "0.1")
set(KAPPTEMPLATE_VERSION "${KAPPTEMPLATE_BASE_VERSION}.${RELEASE_SERVICE_COMPACT_VERSION}")

project(kapptemplate VERSION ${KAPPTEMPLATE_VERSION})

set(QT_MIN_VERSION "5.15.2")
set(KF_MIN_VERSION "5.91.0")

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
include(ECMDeprecationSettings)
if (QT_MAJOR_VERSION STREQUAL "6")
    set(QT_REQUIRED_VERSION "6.4.0")
    set(KF_MIN_VERSION "5.240.0")
    set(KF_MAJOR_VERSION "6")
else()
    set(KF_MAJOR_VERSION "5")
endif()
include(KDEClangFormat)
include(KDEGitCommitHooks)
include(FeatureSummary)

if (BUILD_TESTING)
    find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} REQUIRED COMPONENTS Test)
endif()

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} REQUIRED COMPONENTS Widgets)

find_package(KF${KF_MAJOR_VERSION} ${KF_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons
    ConfigWidgets
    Completion
    Archive
    KIO
    I18n
    DocTools
    # NewStuff
)

ecm_set_disabled_deprecation_versions(
    QT 6.4
    KF 5.91
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

# Excluding templates, because clang-format doesn't know how to handle ${templated} code
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/application/*.cpp
    ${PROJECT_SOURCE_DIR}/src/application*.h
    ${PROJECT_SOURCE_DIR}/tests/*.cpp
    ${PROJECT_SOURCE_DIR}/tests/*.h
)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
