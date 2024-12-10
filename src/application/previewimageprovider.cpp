// SPDX-FileCopyrightText: 2001 Bernd Gehrmann <bernd@kdevelop.org>
// SPDX-FileCopyrightText: 2004-2005 Sascha Cunz <sascha@kdevelop.org>
// SPDX-FileCopyrightText: 2007 Alexander Dymo <adymo@kdevelop.org>
// SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>
// SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "previewimageprovider.h"

#include "logging.h"

#include <KFileUtils>
#include <KTar>
#include <KZip>

#include <QDir>
#include <QFileInfo>
#include <QIcon>
#include <QStandardPaths>

PreviewImageProvider::PreviewImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

QPixmap PreviewImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    const auto data = id.split(u'/');
    if (data.length() != 2) {
        return {};
    }

    const QString iconName = data[0];
    const QString archiveBaseName = data[1];

    if (iconName.isEmpty()) {
        return {};
    }

    // find archive
    const QStringList templatePaths =
        QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, "kdevappwizard/templates/", QStandardPaths::LocateDirectory);
    const QStringList results = KFileUtils::findAllUniqueFiles(templatePaths, {archiveBaseName + QLatin1String(".*")});

    // read icon from archive
    if (!results.isEmpty()) {
        const QString archivePath = results.first();

        QScopedPointer<KArchive> templateArchive;
        if (QFileInfo(archivePath).completeSuffix() == QLatin1String("zip")) {
            templateArchive.reset(new KZip(archivePath));
        } else {
            templateArchive.reset(new KTar(archivePath));
        }

        if (templateArchive->open(QIODevice::ReadOnly)) {
            const KArchiveFile *iconFile = templateArchive->directory()->file(iconName);
            if (iconFile) {
                const auto data = iconFile->data();
                QPixmap pixmap;
                const bool loadSuccess = pixmap.loadFromData(iconFile->data());
                if (loadSuccess) {
                    *size = pixmap.size();
                    return pixmap;
                }
                qCWarning(KAPPTEMPLATE) << "Could not load preview icon" << iconName << "from" << archivePath;
            }
        }
    }

    // support legacy templates with image files installed separately in the filesystem
    const QString iconFilePath = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QLatin1String("kdevappwizard/template_previews/") + iconName);
    if (!iconFilePath.isEmpty()) {
        QPixmap pixmap(iconFilePath);
        if (!pixmap.isNull()) {
            return pixmap;
        }
        qCWarning(KAPPTEMPLATE) << "Could not load preview icon" << iconFilePath << "as wanted for" << archiveBaseName;
    }

    // try theme icon (inofficial feature)
    if (QIcon::hasThemeIcon(iconName)) {
        *size = QSize(128, 128);
        return QIcon::fromTheme(iconName).pixmap(128, 128);
    }

    return {};
}
