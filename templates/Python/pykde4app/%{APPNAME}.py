# File : %{APPNAMELC}.py
import sys
import os
from PyQt4 import QtGui, QtCore
from PyKDE4.kdecore import ki18n, i18n, KCmdLineArgs, KAboutData
from PyKDE4.kdeui import KApplication, KXmlGuiWindow, KStandardAction, KAction, KIcon
from myCalendar import Ui_myCalendar

# We start a new class here
# derived from KXmlGuiWindow
# A calendar is displayed and clicking on a date makes this date be displayed on the label on the bottom

class %{APPNAMELC}(KXmlGuiWindow):
    def __init__(self):
        KXmlGuiWindow.__init__(self)

        self.ui = Ui_myCalendar()
	myWidget = QtGui.QWidget()
        self.ui.setupUi(myWidget)
	self.setCentralWidget(myWidget)
	#set label text to current date
	self.ui.myLabel.setText(str(self.ui.calendarWidget.selectedDate().toPyDate()))
        # Connect the calendar to show the date on the QLabel
        self.connect(self.ui.calendarWidget, QtCore.SIGNAL('selectionChanged()'), self.showDate)
        # Add a quit action
        KStandardAction.quit(app.quit, self.actionCollection())
        # Add an action for display of current month
        curMonthAction = KAction(KIcon("chronometer"), i18n("Show current &month"), self)
        curMonthAction.setWhatsThis(i18n("Show the current month in the calender."))
        self.actionCollection().addAction("showcurrentmonth", curMonthAction)
        self.connect(curMonthAction, QtCore.SIGNAL("triggered(bool)"), self.ui.calendarWidget.showToday)
        # Setup GUI
        self.setupGUI(KXmlGuiWindow.Default, os.path.join(sys.path[0], "%{APPNAME}ui.rc"))

    def showDate(self):
	date = self.ui.calendarWidget.selectedDate()
	self.ui.myLabel.setText(str(date.toPyDate()))

if __name__ == "__main__":
    appName     = "%{APPNAMELC}"
    catalog     = ""
    programName = ki18n("%{APPNAMELC}")
    version     = "0.1"
    description = ki18n("Simple calender viewer")
    license     = KAboutData.License_GPL
    copyright   = ki18n("(c) 2008 Noname")
    text        = ki18n("This application shows a small calender and helps to select a date.")
    homePage    = "http://"
    bugEmail    = "your@email"

    aboutData = KAboutData(appName, catalog, programName, version, description,
        license, copyright, text, homePage, bugEmail)
    aboutData.addAuthor(ki18n("Noname"), ki18n("Developer"),
        "your@email",
        "http://")

    KCmdLineArgs.init(sys.argv, aboutData)

    app = KApplication()
    window = %{APPNAMELC}()
    window.show()
    sys.exit(app.exec_())