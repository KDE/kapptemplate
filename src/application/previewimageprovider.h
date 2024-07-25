// SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QQuickImageProvider>

class PreviewImageProvider : public QQuickImageProvider
{
    Q_OBJECT

public:
    explicit PreviewImageProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
};
