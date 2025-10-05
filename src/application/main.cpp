/*
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>
    SPDX-FileCopyrightText: 2008 Beat Wolf <asraniel@fryx.ch>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <KAboutData>
#include <KIconTheme>
#include <KLocalizedContext>
#include <KLocalizedString>
#define HAVE_STYLE_MANAGER __has_include(<KStyleManager>)
#if HAVE_STYLE_MANAGER
#include <KStyleManager>
#endif

#include <QApplication>
#include <QCommandLineParser>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QRegularExpression>

#include "generator.h"
#include "kapptemplate_version.h"
#include "logging.h"
#include "previewimageprovider.h"

using namespace Qt::StringLiterals;

int main(int argc, char **argv)
{
#if KICONTHEMES_VERSION >= QT_VERSION_CHECK(6, 3, 0)
    KIconTheme::initTheme();
#endif

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

#if HAVE_STYLE_MANAGER
    KStyleManager::initStyle();
#else
#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
    QApplication::setStyle(u"breeze"_s);
#endif
#endif

    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(u"org.kde.desktop"_s);
        QQuickStyle::setFallbackStyle(u"Fusion"_s);
    }

    {
        QCommandLineParser parser;
        parser.addPositionalArgument("name", "Name of the generated project");
        parser.addPositionalArgument("location", "Path where to generate the project");
        parser.addPositionalArgument("author", "Name");
        parser.addPositionalArgument("e-mail", "Mail");
        parser.addPositionalArgument("version", "Version");
        parser.addPositionalArgument("template", "Which template to use");
        QCommandLineOption optionList("list-templates");
        parser.addOption(optionList);
        about.setupCommandLine(&parser);
        parser.process(application);
        about.processCommandLine(&parser);

        if (parser.isSet(optionList)) {
            const auto templates = Generator::templates();
            for (const auto &templateName : templates) {
                QTextStream(stdout) << templateName << Qt::endl;
            }
            return 0;
        } else if (const auto args = parser.positionalArguments(); !args.isEmpty()) {
            if (args.size() != 6) {
                QTextStream(stderr) << "Wrong number of args: " << args.size() << Qt::endl;
                return 1;
            }
            int ret = 0;
            Generator generator;
            QObject::connect(&generator, &Generator::done, &application, [](QString summary) {
                summary.replace(QLatin1StringView("<br />"), QLatin1StringView("\n"));
                summary.replace(QRegularExpression("<.*/?>"), QString());
                QTextStream(stdout) << summary << Qt::endl;
            });
            QObject::connect(&generator, &Generator::errorOccurred, &application, [&ret](const QString &error) {
                ret = 1;
                QTextStream(stderr) << error << Qt::endl;
            });
            generator.setName(args[0]);
            generator.setLocation(args[1]);
            generator.setAuthorName(args[2]);
            generator.setAuthorEmail(args[3]);
            generator.setVersion(args[4]);
            generator.startGeneration(args[5], args[5]);
            return ret;
        }
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.addImageProvider(QLatin1String("preview"), new PreviewImageProvider);
    engine.loadFromModule("org.kde.kapptemplate", "Main");

    return application.exec();
}
