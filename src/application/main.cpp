/***************************************************************************
 *   Copyright  2008 by Anne-Marie Mahfouf <annma@kde.org>                 *
 *   Copyright  2008 by Beat Wolf          <asraniel@fryx.ch>              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#include <KLocalizedString>
#include <KAboutData>

#include <QApplication>
#include <QCommandLineParser>

#include "kapptemplate.h"
#include "logging.h"

#if QT_VERSION >= 0x050500
Q_LOGGING_CATEGORY(KAPPTEMPLATE, "kapptemplate", QtInfoMsg)
#else
Q_LOGGING_CATEGORY(KAPPTEMPLATE, "kapptemplate")
#endif

int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    KLocalizedString::setApplicationDomain("kapptemplate");

    KAboutData about("kapptemplate", i18n("KAppTemplate"), "0.1", i18n("KAppTemplate is a KDE project template generator"), KAboutLicense::GPL, i18n("(C) 2008 Anne-Marie Mahfouf"), QString(), QString(), "submit@bugs.kde.org");
    about.addAuthor(i18n("Anne-Marie Mahfouf"), QString(), "annma AT kde DOT org");
    about.addAuthor(i18n("Sean Wilson"), i18n("Icons from Oxygen Team icons"), "suseux AT googlemail DOT com");

    KAboutData::setApplicationData(about);
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("kapptemplate")));

    KAppTemplate appTemplate;
    QCommandLineParser parser;
    about.setupCommandLine(&parser);

    parser.process(application);
    about.processCommandLine(&parser);

    appTemplate.show();

    return application.exec();
}
