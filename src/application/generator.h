// SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QHash>
#include <QObject>
#include <QtQml/qqmlregistration.h>

class KArchiveDirectory;

class Generator : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QString authorName READ authorName WRITE setAuthorName NOTIFY authorNameChanged)
    Q_PROPERTY(QString authorEmail READ authorEmail WRITE setAuthorEmail NOTIFY authorEmailChanged)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged)

public:
    explicit Generator(QObject *parent = nullptr);

    QString name() const;
    QString location() const;
    QString authorName() const;
    QString authorEmail() const;
    QString version() const;

    void setName(const QString &name);
    void setLocation(const QString &location);
    void setAuthorName(const QString &authorName);
    void setAuthorEmail(const QString &authorEmail);
    void setVersion(const QString &version);

    static QStringList templates();

public Q_SLOTS:
    void startGeneration(const QString &templateName, const QString &generator);

Q_SIGNALS:
    void nameChanged();
    void locationChanged();
    void authorNameChanged();
    void authorEmailChanged();
    void versionChanged();

    void errorOccurred(const QString &errorMessage);
    void progressUpdated(int progress);
    void done(const QString &summary);

private:
    bool unpackArchive(const KArchiveDirectory *dir, const QString &dest, const QStringList &skipList = {}, bool firstCall = true);
    bool extractFileMacros(const QString &entry);

    QHash<QString, QString> m_variables;
    QString m_name;
    QString m_location;
    QString m_authorName;
    QString m_authorEmail;
    QString m_version;
    QString m_initialCommitMessage;
    QStringList m_newFiles;
};
