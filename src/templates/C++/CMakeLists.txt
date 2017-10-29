set(APPTEMPLATE_DIRS
    kde-frameworks5-simple
    kde-frameworks5
)

kde_package_app_templates(TEMPLATES ${APPTEMPLATE_DIRS} INSTALL_DIR ${KDE_INSTALL_KTEMPLATESDIR})
