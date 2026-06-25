set(APPTEMPLATE_DIRS
    kde-frameworks6-simple
    kde-frameworks6
)

kde_package_app_templates(TEMPLATES ${APPTEMPLATE_DIRS} INSTALL_DIR ${KDE_INSTALL_KAPPTEMPLATESDIR})

if(ECM_VERSION VERSION_GREATER_EQUAL 6.28)
    # our own templates
    kde_test_app_template(TEMPLATE kde-frameworks6-simple NAME TestApp)
    kde_test_app_template(TEMPLATE kde-frameworks6 NAME TestApp)

    # templates from modules that cannot depend on kapptemplate for testing
    # as we depend on them
    kde_test_app_template(TEMPLATE kirigami6 NAME TestApp)
    kde_test_app_template(TEMPLATE kirigamiaddons6 NAME TestApp)
endif()
