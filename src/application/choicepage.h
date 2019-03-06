/***************************************************************************
 *   Copyright 2001 Bernd Gehrmann <bernd@kdevelop.org>                    *
 *   Copyright 2004-2005 Sascha Cunz <sascha@kdevelop.org>                 *
 *   Copyright 2007 Alexander Dymo <adymo@kdevelop.org>                    *
 *   Copyright 2008 Anne-Marie Mahfouf <annma@kde.org>                     *
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
    ChoicePage( QWidget *parent = nullptr);
    AppTemplatesModel *templatesModel;
    QString m_baseName;
    bool isComplete () const;
    QString templateName() const { return m_baseName; }

Q_SIGNALS:
    void templateNameChanged(const QString&);

private:
    Ui::choice ui_choice;

private slots:
    /**
    * Saves project name in config file
    */
    void saveConfig();

    void loadFromFile();
#ifdef KAPPTEMLATE_SOLVEDGHNS
    void getMoreTemplates();
#endif

protected slots:
    void itemSelected(const QModelIndex &index);
};

#endif // CHOICEPAGE_H
