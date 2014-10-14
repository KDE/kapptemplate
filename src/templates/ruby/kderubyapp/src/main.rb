require 'korundum4'
require '%{APPNAMELC}.rb'

description = "A ruby KDE 4 Application"
version = "%{VERSION}"

about = KDE::AboutData.new("%{APPNAMELC}", nil, KDE::ki18n("%{APPNAME}"), version, KDE::ki18n(description),
                           KDE::AboutData::License_LGPL, KDE::ki18n("(C) 2008 %{AUTHOR}"), KDE::LocalizedString.new, nil, "%{EMAIL}" )
about.addAuthor( KDE::ki18n("%{AUTHOR}"), KDE::LocalizedString.new, "%{EMAIL}" )
KDE::CmdLineArgs.init(ARGV, about)

options = KDE::CmdLineOptions.new
options.add("+[URL]", KDE::ki18n( "Document to open" ))
KDE::CmdLineArgs.addCmdLineOptions(options)
app = KDE::Application.new

# see if we are starting with session management
if app.sessionRestored?
  KDE::MainWindow.each_restore do |n|
    %{APPNAMEFU}.new.restore(n)
  end
else
  # no session.. just start up normally
  args = KDE::CmdLineArgs.parsedArgs
  if args.count == 0
    %{APPNAMEFU}.new.show
  else
    args.each do |arg|
      %{APPNAMEFU}.new.show
    end
    args.clear
  end
end
app.exec
