# TODO Move all templates to the templates "root" directory and update/improve the kapptemplate_add_app_templates

add_subdirectory(C++)
add_subdirectory(QML)

install(FILES C++/kapp4-qml/kapp4.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/kde-simple/kde-simple.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/kde-frameworks5-simple/kde-frameworks5-simple.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/kde-frameworks5/kde-frameworks5.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/qmake_qt4guiapp/qmake4gui.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/kpartapp/kpartapp.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/akonadiresource/akonadi-resources.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/akonadiserializer/akonadi-serializer.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/runner/runner.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/konqplugin/konqplugin.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/cmake_qt5guiapp/cmake_qt5guiapp.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES QML/qt5-qml2/qt5-qml2.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
