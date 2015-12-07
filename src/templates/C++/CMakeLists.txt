set(apptemplate_DIRS
    kapp4-qml
    kde-simple
    kde-frameworks5-simple
    kde-frameworks5
    runner
    ktexteditor
    konqplugin
    qmake_qt4guiapp
    kpartapp
    akonadiresource
    akonadiserializer
    cmake_qt5guiapp
)

kapptemplate_add_app_templates(${apptemplate_DIRS})
