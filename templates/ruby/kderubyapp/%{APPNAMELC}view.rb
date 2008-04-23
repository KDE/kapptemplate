require '%{APPNAMELC}view_base.rb'

class %{APPNAME}View < Qt::Widget
  signals 'signalChangeStatusbar(QString)', 'signalChangeCaption(QString)'
  slots :switchColors, :settingsChanged

  def initialize( parent )
    super(parent)
    @ui = Ui_%{APPNAMELC}view_base.new
    @ui.setupUi(self)
    settingsChanged()
    setAutoFillBackground(true)
  end

private
  def switchColors()
#     # switch the foreground/background colors of the label
#     color = Settings.col_background
#     Settings::setCol_background( Settings::col_foreground() );
#     Settings::setCol_foreground( color );
#     settingsChanged();
  end
  def settingsChanged()
#     pal = Qt::Palette.new
#     pal.color = Qt::Palette::Window, Settings::col_background
#     pal.setColor( Qt::Palette::WindowText, Settings::col_foreground)
#     @ui_%{APPNAMELC}view_base.kcfg_sillyLabel.palette = pal
# 
#     # i18n : internationalization
#     ui_%{APPNAMELC}view_base.kcfg_sillyLabel.text = i18n("This project is %1 days old",Settings::val_time()) 
#     emit signalChangeStatusbar( i18n("Settings changed") );
  end
end
