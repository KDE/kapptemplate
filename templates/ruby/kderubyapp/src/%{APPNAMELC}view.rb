require 'ui_%{APPNAMELC}view_base.rb'

class %{APPNAMEFU}View < Qt::Widget
  signals 'signalChangeStatusbar(QString)', 'signalChangeCaption(QString)'
  slots :switchColors, :settingsChanged

  def initialize( parent )
    super(parent)
    @ui = Ui_%{APPNAMEFU}view_base.new
    @ui.setupUi(self)
    settingsChanged()
    setAutoFillBackground(true)
  end

private
  def switchColors()
#     # switch the foreground/background colors of the label
#     color = Settings.col_background
#     Settings.setCol_background( Settings.col_foreground )
#     Settings.setCol_foreground( color )
#     settingsChanged()
  end

  def settingsChanged()
#     pal = Qt::Palette.new
#     pal.setColor(Qt::Palette::Window, Settings::col_background)
#     pal.setColor( Qt::Palette::WindowText, Settings::col_foreground)
#     @ui.kcfg_sillyLabel.palette = pal
# 
#     # i18n : internationalization
#     @ui.kcfg_sillyLabel.text = KDE::i18n("This project is %%1 days old", Settings.val_time()) 
#     emit signalChangeStatusbar( KDE::i18n("Settings changed") )
  end
end
