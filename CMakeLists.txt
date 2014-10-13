cmake_minimum_required(VERSION 2.8.12)
project(kapptemplate)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(ECMInstallIcons)
include(ECMAddTests)
include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)
include(FeatureSummary)
include(KAppTemplateMacro)

find_package(Qt5 REQUIRED COMPONENTS Test)
find_package(KF5 REQUIRED COMPONENTS KDELibs4Support CoreAddons ConfigWidgets Archive KIO Bookmarks Solid JobWidgets)

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

add_subdirectory(doc)
add_subdirectory(icons)
add_subdirectory(templates)
add_subdirectory(tests)

set(kapptemplate_SRCS
   kapptemplate.cpp
   main.cpp
   apptemplatesmodel.cpp
   apptemplateitem.cpp
   generatepage.cpp
   choicepage.cpp
)

qt5_wrap_ui(kapptemplate_SRCS introduction.ui choice.ui properties.ui generate.ui)

kconfig_add_kcfg_files(kapptemplate_SRCS prefs.kcfgc)

add_executable(kapptemplate ${kapptemplate_SRCS})

target_link_libraries(kapptemplate KF5::KDELibs4Support KF5::CoreAddons KF5::ConfigWidgets KF5::Archive KF5::KIOCore)

install(TARGETS kapptemplate ${INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS kapptemplate.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR})
install(FILES kapptemplate.kcfg  DESTINATION  ${KCFG_INSTALL_DIR})
install(FILES default.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/kapp4/kapp4.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/kde-simple/kde-simple.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/kde-frameworks5-simple/kde-frameworks5-simple.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/kde-frameworks5/kde-frameworks5.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/plasmoid/plasma-applet.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/ruby/kderubyapp/kderubyapp.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/Python/pyqt4app/pyqt4app.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/Python/pykde4app/pykde4.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/qmake_qt4guiapp/qmake4gui.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/kpartapp/kpartapp.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/akonadiresource/akonadi-resources.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/akonadiserializer/akonadi-serializer.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/runner/runner.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/konqplugin/konqplugin.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/QML/qml-plasmoid/qml-plasmoid.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/QML/qt5-qml2/qt5-qml2.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
