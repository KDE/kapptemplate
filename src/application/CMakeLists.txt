ecm_setup_version(${KAPPTEMPLATE_VERSION}
    VARIABLE_PREFIX KAPPTEMPLATE
    VERSION_HEADER kapptemplate_version.h
)

add_executable(kapptemplate)

target_sources(kapptemplate PRIVATE
   kapptemplate.cpp
   main.cpp
   apptemplatesmodel.cpp
   apptemplateitem.cpp
   generatepage.cpp
   choicepage.cpp
)

ecm_qt_declare_logging_category(kapptemplate
    HEADER logging.h
    IDENTIFIER KAPPTEMPLATE
    CATEGORY_NAME kapptemplate
    DESCRIPTION "KAppTemplate"
    EXPORT KAPPTEMPLATE
)

ki18n_wrap_ui(kapptemplate
    introduction.ui
    choice.ui
    properties.ui
    generate.ui
)

kconfig_add_kcfg_files(kapptemplate prefs.kcfgc)

target_link_libraries(kapptemplate
    KF6::CoreAddons
    KF6::ConfigWidgets
    KF6::Completion
    KF6::KIOWidgets
    KF6::Archive
    KF6::KIOCore
    KF6::I18n
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
