install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(kde_datadir)/kapptemplate/admin
	for file in *; do \
		if [ -f $$file -a $$file != 'Makefile' -a $$file != 'Makefile.in' -a $$file != 'Makefile.am' ]; then \
			$(INSTALL_DATA) $(srcdir)/$$file \
				$(DESTDIR)$(kde_datadir)/kapptemplate/admin/$$file; \
		fi \
	done

uninstall-local:
	-/bin/rm -rf $(DESTDIR)$(kde_datadir)/kapptemplate/admin
