# In this CMakeLists.txt we define which files
# are used to compile the application
set(%{APPNAMELC}_SRCS
   %{APPNAMELC}.cpp
   main.cpp
 )

# Run ui files through uic
kde4_add_ui_files(%{APPNAMELC}_SRCS %{APPNAMELC}.ui)

# Set the name of the application
kde4_add_executable(%{APPNAMELC} ${%{APPNAMELC}_SRCS})

# Select which libraries we need to link to
target_link_libraries(%{APPNAMELC} ${KDE4_KDEUI_LIBS})

# Tell cmake to install the application binary
install(TARGETS %{APPNAMELC} ${INSTALL_TARGETS_DEFAULT_ARGS})

# Install the .desktop file
install( PROGRAMS %{APPNAMELC}.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
