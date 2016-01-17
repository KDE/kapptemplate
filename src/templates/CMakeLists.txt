# TODO Move all templates to the templates "root" directory and update/improve the kapptemplate_add_app_templates

add_subdirectory(C++)

install(FILES C++/kapp4-qml/kapp4.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/kde-simple/kde-simple.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/kde-frameworks5-simple/kde-frameworks5-simple.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/kde-frameworks5/kde-frameworks5.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/kpartapp/kpartapp.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/akonadiresource/akonadi-resources.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/akonadiserializer/akonadi-serializer.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/runner/runner.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
install(FILES C++/konqplugin/konqplugin.png DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_previews)
