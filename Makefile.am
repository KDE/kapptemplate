SUBDIRS=admin appframework existing kapp kpartapp kpartplugin

VERSION := `cat $(srcdir)/VERSION`

bin_SCRIPTS = kapptemplate

kapptemplate: kapptemplate.in
	echo "#!/usr/bin/env bash" > kapptemplate; \
	echo "INSTALLED_SHARE_DIR=$(kde_datadir)/kapptemplate" >> kapptemplate; \
	echo "KAPPTEMPLATEVERSION=$(VERSION)" >> kapptemplate; \
	cat $(srcdir)/kapptemplate.in >> kapptemplate; \
	chmod 755 kapptemplate

databindir = $(kde_datadir)/kapptemplate/bin
databin_SCRIPTS = mkinstalldirs

moduledir = $(kde_datadir)/kapptemplate/include
module_DATA = kapptemplate.common kapptemplate.module \
	       kpartplugin.module kpartapp.module existing.module
