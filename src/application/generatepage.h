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
    GeneratePage(QWidget *parent = nullptr);

private:
    Ui::generate ui_generate;
    QHash<QString, QString> m_variables;
    bool unpackArchive(const KArchiveDirectory *dir, const QString &dest, const QStringList& skipList = QStringList());
    bool extractFileMacros(const QString &entry);

    void initializePage();
    void displayError(const QString &error);

    QString templateName;
    QString feedback;
};

#endif // GENERATEPAGE_H
