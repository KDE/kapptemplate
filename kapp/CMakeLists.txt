add_subdirectory( no-exe) 

install(FILES appview.h index.docbook app-CMakeLists.txt src-CMakeLists.txt doc-CMakeLists.txt apppref.cpp icons-CMakeLists.txt app.cpp app.kcfg settings.kcfgc apppref.h hi16-app-app.png main.cpp app-desktop appui.rc hi32-app-app.png app.h appview.cpp hi48-app-app.png org.kde.app.App.xml DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/kapp)
