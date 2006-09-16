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

FILE(WRITE ${CMAKE_SOURCE_DIR}/kapptemplate/kapptemplate "#!/usr/bin/env bash \nINSTALLED_SHARE_DIR=${DATA_INSTALL_DIR}/kapptemplate \nKAPPTEMPLATEVERSION=${VERSION}")
#put kapptemplate.in n a var and then append it to kapptemplate - maybe that could be done in 1 command
FILE(READ ${CMAKE_SOURCE_DIR}/kapptemplate/kapptemplate.in temp)
FILE(APPEND ${CMAKE_SOURCE_DIR}/kapptemplate/kapptemplate ${temp} )
EXECUTE_PROCESS(COMMAND chmod 755 ${CMAKE_SOURCE_DIR}/kapptemplate/kapptemplate)


########### install files ###############

#bin_SCRIPTS = kapptemplate
install(PROGRAMS kapptemplate DESTINATION ${BIN_INSTALL_DIR})

#databindir = $(kde_datadir)/kapptemplate/bin
#databin_SCRIPTS = mkinstalldirs
install(PROGRAMS mkinstalldirs DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/bin)

#moduledir = $(kde_datadir)/kapptemplate/include
#module_DATA = kapptemplate.common kapptemplate.module \
	       #kpartplugin.module kpartapp.module existing.module
install( FILES kapptemplate.common kapptemplate.module kpartplugin.module kpartapp.module existing.module  DESTINATION  ${DATA_INSTALL_DIR}/kapptemplate/include )