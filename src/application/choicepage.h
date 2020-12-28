/*
    SPDX-FileCopyrightText: 2001 Bernd Gehrmann <bernd@kdevelop.org>
    SPDX-FileCopyrightText: 2004-2005 Sascha Cunz <sascha@kdevelop.org>
    SPDX-FileCopyrightText: 2007 Alexander Dymo <adymo@kdevelop.org>
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHOICEPAGE_H
#define CHOICEPAGE_H

#include <QWizardPage>

#include "ui_choice.h"

class AppTemplatesModel;

class ChoicePage : public QWizardPage
{
    Q_OBJECT
    Q_PROPERTY(QString templateName READ templateName NOTIFY templateNameChanged)

public:
    explicit ChoicePage( QWidget *parent = nullptr);

    AppTemplatesModel *templatesModel;
    QString m_baseName;
    bool isComplete () const override;
    QString templateName() const { return m_baseName; }

Q_SIGNALS:
    void templateNameChanged(const QString&);

private:
    Ui::choice ui_choice;

private Q_SLOTS:
    /**
    * Saves project name in config file
    */
    void saveConfig();

    void loadFromFile();
#ifdef KAPPTEMLATE_SOLVEDGHNS
    void getMoreTemplates();
#endif

protected Q_SLOTS:
    void itemSelected(const QModelIndex &index);
};

#endif // CHOICEPAGE_H
