set(%{APPNAMELC}_ICONS
  hi16-apps-%{APPNAMELC}.png
  hi22-apps-%{APPNAMELC}.png
  hi32-apps-%{APPNAMELC}.png
  hi48-apps-%{APPNAMELC}.png
  hisc-apps-%{APPNAMELC}.svgz
)

ecm_install_icons(ICONS ${%{APPNAMELC}_ICONS} DESTINATION ${ICON_INSTALL_DIR} THEME hicolor)
