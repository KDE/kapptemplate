#SUBDIRS=no-exe
add_subdirectory( no-exe) 

#frameworkdir = $(kde_datadir)/kapptemplate/appframework
#framework_DATA = AUTHORS INSTALL COPYING NEWS  app.lsm \
	#app.spec configure.in.in.in README base-Makefile.am \
	#ChangeLog VERSION base-Makefile.cvs po-Makefile.am

install(FILES AUTHORS INSTALL COPYING NEWS  app.lsm app.spec configure.in.in.in README base-Makefile.am ChangeLog VERSION base-Makefile.cvs po-Makefile.am DESTINATION ${DATA_INSTALL_DIR}/kapptemplate/appframework)