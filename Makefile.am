SUBDIRS=admin appframework existing kapp kpartapp kpartplugin

VERSION := `cat $(srcdir)/VERSION`

bin_PROGRAMS = kapptemplate
kapptemplate_SOURCES =

all:
	@echo "#!/usr/bin/env bash" > ${PWD}/kapptemplate; \
	echo "INSTALLED_SHARE_DIR=$(kde_datadir)/kapptemplate" >> ${PWD}/kapptemplate; \
	echo "KAPPTEMPLATEVERSION=$(VERSION)" >> ${PWD}/kapptemplate; \
	cat $(srcdir)/kapptemplate.in >> ${PWD}/kapptemplate; \
	chmod 755 ${PWD}/kapptemplate

install-exec-local:
	$(mkinstalldirs) $(DESTDIR)$(kde_datadir)/kapptemplate/bin
	$(INSTALL_SCRIPT) ${PWD}/mkinstalldirs $(DESTDIR)$(kde_datadir)/kapptemplate/bin

moduledir = $(kde_datadir)/kapptemplate/include
module_DATA = kapptemplate.common kapptemplate.module \
	       kpartplugin.module kpartapp.module existing.module
