require 'korundum4'
require '${APP_NAME_LC}.rb'

description = "A ruby KDE 4 Application"
version = "${APP_VERSION}"

about = KDE::AboutData.new(
    "${APP_NAME_LC}",
    Qt::ByteArray.new(),
    KDE::ki18n("${APP_NAME}"),
    Qt::ByteArray.new(version),
    KDE::ki18n(description),
    KDE::AboutData::License_LGPL,
    KDE::ki18n("(C) 2007 ${AUTHOR}"),
    KDE::LocalizedString.new,
    Qt::ByteArray.new(),
    "${EMAIL}" )

about.addAuthor( KDE::ki18n("${AUTHOR}"), KDE::LocalizedString.new(), "${EMAIL}" )
KDE::CmdLineArgs::init(ARGV, about)
options = KDE::CmdLineOptions.new
options.add("+[URL]", KDE::ki18n( "Document to open" ))

KDE::CmdLineArgs::addCmdLineOptions(options)

app = KDE::Application.new

widget = ${APP_NAME}.new

# see if we are starting with session management
if(app.isSessionRestored())
  KDE::RESTORE(${APP_NAME});
else
  # no session.. just start up normally
  args = KDE::CmdLineArgs::parsedArgs()
  if(args.count() == 0)
    widget->show();
  else
    i = 0
    while(i < args.count())
      widget.show()
    end
    args.clear()
  end
end
return app.exec()
