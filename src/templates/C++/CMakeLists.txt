set(APPTEMPLATE_DIRS
    kde-frameworks6-simple
    kde-frameworks6
)

kde_package_app_templates(TEMPLATES ${APPTEMPLATE_DIRS} INSTALL_DIR ${KDE_INSTALL_KAPPTEMPLATESDIR})
