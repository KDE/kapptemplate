set(kapptemplate_ICONS
  16-apps-kapptemplate.png
  22-apps-kapptemplate.png
  32-apps-kapptemplate.png
  48-apps-kapptemplate.png
  64-apps-kapptemplate.png
  128-apps-kapptemplate.png
  sc-apps-kapptemplate.svg
)

ecm_install_icons(ICONS ${kapptemplate_ICONS} DESTINATION ${KDE_INSTALL_ICONDIR} THEME hicolor)
