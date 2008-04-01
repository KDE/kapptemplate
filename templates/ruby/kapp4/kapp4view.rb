require '${APP_NAME_LC}view_base.rb'

class ${APP_NAME}View < Qt::Widget
  signals 'signalChangeStatusbar(const QString& text)', 'signalChangeCaption(const QString& text)'
  slots 'switchColors()', 'settingsChanged()'
  def initialize( parent )
    super(parent)
    @ui = Ui_${APP_NAME}view_base.new
    @ui.setupUi(self)
    settingsChanged()
    setAutoFillBackground(true)
  end

private
  def switchColors()
#     # switch the foreground/background colors of the label
#     QColor color = Settings::col_background();
#     Settings::setCol_background( Settings::col_foreground() );
#     Settings::setCol_foreground( color );
#     settingsChanged();
  end
  def settingsChanged()
#     QPalette pal;
#     pal.setColor( QPalette::Window, Settings::col_background());
#     pal.setColor( QPalette::WindowText, Settings::col_foreground());
#     ui_${APP_NAME_LC}view_base.kcfg_sillyLabel->setPalette( pal );
# 
#     // i18n : internationalization
#     ui_${APP_NAME_LC}view_base.kcfg_sillyLabel->setText( i18n("This project is %1 days old",Settings::val_time()) );
#     emit signalChangeStatusbar( i18n("Settings changed") );
  end
end
