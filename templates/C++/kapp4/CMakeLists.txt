install(FILES Messages.sh description.txt kapp4.cpp kapp4.h kapp4-CMakeLists.txt main.cpp kapp4-desktop kapp4view.cpp kapp4view.h settings.kcfgc kapp4ui.rc kapp4-desktop kapp4.kcfg prefs_base.ui kapp4view_base.ui DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/C++/kapp4)

 install(FILES kapp4.kdevtemplate DESTINATION ${DATA_INSTALL_DIR}/kdevappwizard/template_descriptions)
 install(FILES kapp4.png DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/pics)

