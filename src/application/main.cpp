/*
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>
    SPDX-FileCopyrightText: 2008 Beat Wolf <asraniel@fryx.ch>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <KAboutData>
#include <KLocalizedContext>
#include <KLocalizedString>

#include <QApplication>
#include <QCommandLineParser>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "kapptemplate_version.h"
#include "logging.h"
#include "previewimageprovider.h"

int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    KLocalizedString::setApplicationDomain("kapptemplate");

    KAboutData about("kapptemplate",
                     i18n("KAppTemplate"),
                     QStringLiteral(KAPPTEMPLATE_VERSION_STRING),
                     i18n("KAppTemplate is a KDE project template generator"),
                     KAboutLicense::GPL,
                     i18n("(C) 2008 Anne-Marie Mahfouf"),
                     QString(),
                     QStringLiteral("https://apps.kde.org/kapptemplate"),
                     "submit@bugs.kde.org");
    about.addAuthor(i18n("Anne-Marie Mahfouf"), QString(), "annma AT kde DOT org");
    about.addAuthor(i18n("Sean Wilson"), i18n("Icons from Oxygen Team icons"), "suseux AT googlemail DOT com");

    KAboutData::setApplicationData(about);
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("kapptemplate")));

    QCommandLineParser parser;
    about.setupCommandLine(&parser);

    parser.process(application);
    about.processCommandLine(&parser);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.addImageProvider(QLatin1String("preview"), new PreviewImageProvider);
    engine.loadFromModule("org.kde.kapptemplate", "Main");

    return application.exec();
}
