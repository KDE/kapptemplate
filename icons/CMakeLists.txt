set(kapptemplate_ICONS
  hi128-apps-kapptemplate.png
  hi16-apps-kapptemplate.png
  hi22-apps-kapptemplate.png
  hi32-apps-kapptemplate.png
  hi48-apps-kapptemplate.png
  hi64-apps-kapptemplate.png
  hisc-apps-kapptemplate.svg
)

ecm_install_icons(ICONS ${kapptemplate_ICONS} DESTINATION ${ICON_INSTALL_DIR} THEME hicolor)
