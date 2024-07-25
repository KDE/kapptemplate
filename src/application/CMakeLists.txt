ecm_setup_version(${KAPPTEMPLATE_VERSION}
    VARIABLE_PREFIX KAPPTEMPLATE
    VERSION_HEADER kapptemplate_version.h
)

add_executable(kapptemplate)

qt_add_qml_module(kapptemplate
    URI org.kde.kapptemplate
    QML_FILES
        Main.qml
        IntroductionPage.qml
        ChoicePage.qml
        ConfigurePage.qml
        GeneratorPage.qml
    RESOURCES
        konqi-app-dev.png
    SOURCES
        main.cpp
        apptemplatesmodel.cpp
        apptemplateitem.cpp
        generator.cpp
        previewimageprovider.cpp
)

ecm_qt_declare_logging_category(kapptemplate
    HEADER logging.h
    IDENTIFIER KAPPTEMPLATE
    CATEGORY_NAME kapptemplate
    DESCRIPTION "KAppTemplate"
    EXPORT KAPPTEMPLATE
)

kconfig_add_kcfg_files(kapptemplate prefs.kcfgc)

target_link_libraries(kapptemplate PRIVATE
    KF6::CoreAddons
    KF6::ConfigWidgets
    KF6::Completion
    KF6::KIOWidgets
    KF6::Archive
    KF6::KIOCore
    KF6::I18n
    Qt::Quick
    # KF6::NewStuff
)

install(TARGETS kapptemplate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS org.kde.kapptemplate.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.kapptemplate.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES kapptemplate.kcfg DESTINATION ${KDE_INSTALL_KCFGDIR})

ecm_qt_install_logging_categories(
    EXPORT KAPPTEMPLATE
    FILE kapptemplate.categories
    DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
)

# don't install for now, needs to cooperate somehow with kdevplatform/plugins/appwizard/kdevappwizard.knsrc
# install(FILES kapptemplate.knsrc DESTINATION ${KDE_INSTALL_CONFDIR})
