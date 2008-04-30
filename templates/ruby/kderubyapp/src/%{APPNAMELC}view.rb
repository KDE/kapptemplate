require 'ui_%{APPNAMELC}view_base.rb'
require 'settings.rb'

class %{APPNAMEFU}View < Qt::Widget
  signals 'signalChangeStatusbar(QString)', 'signalChangeCaption(QString)'
  slots :switchColors, :settingsChanged

  attr_reader :settings

  def initialize( parent )
    super(parent)
    @ui = Ui_%{APPNAMEFU}view_base.new
    @ui.setupUi(self)
    # Note that the Settings class is a singleton
    @settings = Settings.instance
    settingsChanged()
    setAutoFillBackground(true)
  end

private
  def switchColors()
    # switch the foreground/background colors of the label
    color = @settings.col_background
    @settings.setCol_background( @settings.col_foreground )
    @settings.setCol_foreground( color )
    settingsChanged()
  end

  def settingsChanged()
    pal = Qt::Palette.new
    pal.setColor(Qt::Palette::Window, @settings.col_background)
    pal.setColor( Qt::Palette::WindowText, @settings.col_foreground)
    @ui.kcfg_sillyLabel.palette = pal
 
    # i18n : internationalization
    # @ui.kcfg_sillyLabel.text = KDE::i18n("This project is %%1 days old", @settings.val_time.to_s) 
    @ui.kcfg_sillyLabel.text = "This project is #{@settings.val_time} days old"
    emit signalChangeStatusbar( KDE::i18n("Settings changed") )
  end
end
