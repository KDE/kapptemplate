project(kapptemplate)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

include(KAppTemplateMacro)

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

kde4_add_ui_files(kapptemplate_SRCS introduction.ui choice.ui properties.ui generate.ui)

kde4_add_kcfg_files(kapptemplate_SRCS prefs.kcfgc )

kde4_add_app_icon(kapptemplate_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/icons/hi*-app-kapptemplate.png")

kde4_add_executable(kapptemplate ${kapptemplate_SRCS})

target_link_libraries(kapptemplate ${KDE4_KIO_LIBS})

install(TARGETS kapptemplate ${INSTALL_TARGETS_DEFAULT_ARGS} )

########### install files ###############

install( PROGRAMS kapptemplate.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES kapptemplate.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install(FILES default.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/kapp4/kapp4.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES templates/C++/kde-simple/kde-simple.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
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
