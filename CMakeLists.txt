#SUBDIRS=admin appframework existing kapp kpartapp kpartplugin
add_subdirectory( appframework) 
add_subdirectory( existing ) 
add_subdirectory( kapp) 
add_subdirectory( kpartapp)
add_subdirectory( kpartplugin)

#VERSION := `cat $(srcdir)/VERSION`
FILE(READ ${CMAKE_SOURCE_DIR}/kapptemplate/VERSION VERSION)

#kapptemplate: kapptemplate.in
	#echo "#!/usr/bin/env bash" > kapptemplate; \
	#echo "INSTALLED_SHARE_DIR=$(kde_datadir)/kapptemplate" >> kapptemplate; \
	#echo "KAPPTEMPLATEVERSION=$(VERSION)" >> kapptemplate; \
	#cat $(srcdir)/kapptemplate.in >> kapptemplate; \
	#chmod 755 kapptemplate

FILE(WRITE ${CMAKE_CURRENT_BINARY_DIR}/kapptemplate "#!/usr/bin/env bash \nINSTALLED_SHARE_DIR=${DATA_INSTALL_DIR}/kapptemplate \nKAPPTEMPLATEVERSION=${VERSION}")
#put kapptemplate.in n a var and then append it to kapptemplate - maybe that could be done in 1 command
FILE(READ ${CMAKE_SOURCE_DIR}/kapptemplate/kapptemplate.in temp)
FILE(APPEND ${CMAKE_CURRENT_BINARY_DIR}/kapptemplate ${temp} )

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/kapptemplate DESTINATION ${BIN_INSTALL_DIR} PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)

#databindir = $(kde_datadir)/kapptemplate/bin
#databin_SCRIPTS = mkinstalldirs
install(PROGRAMS mkinstalldirs DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/bin)

#moduledir = $(kde_datadir)/kapptemplate/include
#module_DATA = kapptemplate.common kapptemplate.module \
	       #kpartplugin.module kpartapp.module existing.module
install( FILES kapptemplate.common kapptemplate.module kpartplugin.module kpartapp.module existing.module  DESTINATION  ${DATA_INSTALL_DIR}/kapptemplate/include )
