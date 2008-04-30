require 'ui_prefs_base.rb'
require '%{APPNAMELC}view.rb'

class %{APPNAMEFU} < KDE::XmlGuiWindow
# Default Constructor
  slots :fileNew, :optionsPreferences, :setupActions

  def initialize()
    super()
    # accept dnd
    setAcceptDrops(true)

    # initialise the view
    @view = %{APPNAMEFU}View.new(self)

    # tell the KXmlGuiWindow that this is indeed the main widget
    setCentralWidget(@view)

    # then, setup our actions
    setupActions

    # add a status bar
    statusBar.show

    # a call to KXmlGuiWindow::setupGUI() populates the GUI
    # with actions, using KXMLGUI.
    # It also applies the saved mainwindow settings, if any, and ask the
    # mainwindow to automatically save settings if changed: window size,
    # toolbar position, icon size, etc.
    setupGUI()
  end

private
  def fileNew()
    %{APPNAMEFU}.new.show
  end

  def optionsPreferences
    # The preference dialog is derived from prefs_base.ui
    #
    # compare the names of the widgets in the .ui file
    # to the names of the variables in the .kcfg file
    # avoid to have 2 dialogs shown
    if KDE::ConfigDialog.showDialog("settings")
      return
    end
    dialog = KDE::ConfigDialog.new(self, "settings", @view.settings)
    generalSettingsDlg = Qt::Widget.new
    @ui = Ui_Prefs_base.new
    @ui.setupUi(generalSettingsDlg)
    dialog.addPage(generalSettingsDlg, KDE::i18n("General"), "package_setting")
    connect(dialog, SIGNAL('settingsChanged(QString)'), @view, SLOT('settingsChanged()'))
    dialog.setAttribute(Qt::WA_DeleteOnClose)
    dialog.show
  end

private
  def setupActions()
    KDE::StandardAction.openNew(self, SLOT(:fileNew), actionCollection)
    KDE::StandardAction.quit($kapp, SLOT(:closeAllWindows), actionCollection)

    KDE::StandardAction.preferences(self, SLOT(:optionsPreferences), actionCollection)

    # custom menu and menu item - the slot is in the class ${APP_NAME}View
    custom = KDE::Action.new(KDE::Icon.new("colorize"), i18n("Swi&tch Colors"), self)
    actionCollection.addAction( "switch_action", custom )
    connect(custom, SIGNAL('triggered(bool)'), @view, SLOT(:switchColors))
  end

end
