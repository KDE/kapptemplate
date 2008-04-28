project(kapptemplate)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

include(KAppTemplateMacro)

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

kde4_add_executable(kapptemplate ${kapptemplate_SRCS})

target_link_libraries(kapptemplate ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS})

install(TARGETS kapptemplate DESTINATION ${BIN_INSTALL_DIR} )

########### install files ###############

install( FILES kapptemplate.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES kapptemplate.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install(FILES default.png DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/pics)
install(FILES templates/C++/kapp4/kapp4.kdevtemplate DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_descriptions)
install(FILES templates/C++/kapp4/kapp4.png DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/pics)
install(FILES templates/C++/plasmoid/plasmoid.kdevtemplate DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_descriptions)
install(FILES templates/C++/plasmoid/plasma-applet.png DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/pics)
install(FILES templates/ruby/kderubyapp/kderubyapp.kdevtemplate DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_descriptions)
install(FILES templates/ruby/kderubyapp/kderubyapp.png DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/pics)
install(FILES templates/Python/pyqt4app/pyqt4app.kdevtemplate DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_descriptions)
install(FILES templates/Python/pyqt4app/pyqt4app.png DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/pics)
install(FILES templates/Python/pykde4app/pykde4app.kdevtemplate DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_descriptions)
install(FILES templates/Python/pykde4app/pykde4.png DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/pics)
install(FILES templates/C++/qmake_qt4guiapp/qmake_qt4guiapp.kdevtemplate DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_descriptions)
install(FILES templates/C++/qmake_qt4guiapp/qmake4gui.png DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/pics)
install(FILES templates/C++/kpartapp/kpartapp.kdevtemplate DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_descriptions)
install(FILES templates/C++/kpartapp/kpartapp.png DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/pics)
