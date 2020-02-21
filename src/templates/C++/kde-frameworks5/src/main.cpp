/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application header
#include "%{APPNAMELC}window.h"
#include "%{APPNAMELC}debug.h"

// KF headers
#include <KCrash>
#include <KDBusService>
#include <KAboutData>
#include <KLocalizedString>

// Qt headers
#include <QApplication>
#include <QCommandLineParser>
#include <QIcon>
#include <QLoggingCategory>


int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    KLocalizedString::setApplicationDomain("%{APPNAMELC}");
    KCrash::initialize();

    KAboutData aboutData( QStringLiteral("%{APPNAMELC}"),
                          i18n("%{APPNAME}"),
                          QStringLiteral("%{VERSION}"),
                          i18n("A Simple Application written with KDE Frameworks"),
                          KAboutLicense::GPL,
                          i18n("Copyright %{CURRENT_YEAR}, %{AUTHOR} <%{EMAIL}>"));

    aboutData.addAuthor(i18n("%{AUTHOR}"),i18n("Author"), QStringLiteral("%{EMAIL}"));
    aboutData.setOrganizationDomain("example.org");
    aboutData.setDesktopFileName(QStringLiteral("org.example.%{APPNAMELC}"));

    KAboutData::setApplicationData(aboutData);
    application.setWindowIcon(QIcon::fromTheme(QStringLiteral("%{APPNAMELC}")));

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    parser.process(application);
    aboutData.processCommandLine(&parser);

    KDBusService appDBusService(KDBusService::Multiple | KDBusService::NoExitOnFailure);

    %{APPNAME}Window *window = new %{APPNAME}Window;
    window->show();

    return application.exec();
}
