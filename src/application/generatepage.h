/*
    SPDX-FileCopyrightText: 2001 Bernd Gehrmann <bernd@kdevelop.org>
    SPDX-FileCopyrightText: 2004-2005 Sascha Cunz <sascha@kdevelop.org>
    SPDX-FileCopyrightText: 2007 Alexander Dymo <adymo@kdevelop.org>
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GENERATEPAGE_H
#define GENERATEPAGE_H

#include <KArchive>
#include <KArchiveDirectory>

#include <QWizardPage>
#include <QHash>

#include "kapptemplate.h"
#include "ui_generate.h"

class GeneratePage : public QWizardPage
{
    Q_OBJECT

public:
    explicit GeneratePage(QWidget *parent = nullptr);

private:
    Ui::generate ui_generate;
    QHash<QString, QString> m_variables;
    bool unpackArchive(const KArchiveDirectory *dir, const QString &dest, const QStringList& skipList = QStringList());
    bool extractFileMacros(const QString &entry);

    void initializePage() override;
    void displayError(const QString &error);

    QString templateName;
    QString feedback;
};

#endif // GENERATEPAGE_H
