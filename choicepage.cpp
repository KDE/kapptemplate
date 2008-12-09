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

#include <QString>
#include <QPixmap>
#include <QStandardItem>

#include <KDebug>
#include <kstandarddirs.h>

#include "choicepage.h"
#include "prefs.h"
#include "apptemplatesmodel.h"

ChoicePage::ChoicePage( QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(i18n("Choose your project template"));
    ui_choice.setupUi(this);
    //Get the model
    templatesModel = new AppTemplatesModel(this);
    templatesModel->refresh();
    ui_choice.appTree->setModel(templatesModel); 
    ui_choice.appTree->expandAll();
    connect(ui_choice.kcfg_appName, SIGNAL(textChanged(const QString &)), this, SIGNAL(completeChanged()));
    connect(this, SIGNAL(completeChanged()), this, SLOT(saveConfig()));
    connect(ui_choice.appTree->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(itemSelected(QModelIndex)));
    QRegExp rx("[a-zA-Z0-9_]*");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui_choice.kcfg_appName->setValidator(validator);
    registerField("appName*", ui_choice.kcfg_appName);
}

bool ChoicePage::isComplete () const{
    if(!m_baseName.isEmpty() && !ui_choice.kcfg_appName->text().isEmpty()){
        return true;
    }

    return false;
}

void ChoicePage::saveConfig()
{
    Prefs::setAppName(ui_choice.kcfg_appName->text());
    Prefs::self()->writeConfig();
}

void ChoicePage::itemSelected(const QModelIndex &index)
{
    if (!index.isValid()){
        emit completeChanged();
	return;
    }
    //get picture 
    KStandardDirs* dirs = KGlobal::dirs();
    kDebug() << index.data(Qt::UserRole+2);
    QString picPath = dirs->findResource("apptemplate_previews", index.data(Qt::UserRole+2).toString());
    if (index.data(Qt::UserRole+2).toString().isEmpty()) {
	picPath = dirs->findResource("apptemplate_previews", "default.png");//default if none
    }
    QPixmap pixmap(picPath);
    ui_choice.pictureLabel->setPixmap(pixmap);
    //and description
    QString description;
    if (index.data(Qt::UserRole+1).toString().isEmpty())  {
	description = i18n("Template description");//default if none
    } else {
	description = index.data(Qt::UserRole+1).toString();
    }
    ui_choice.descriptionLabel->setText(description);
    //Template view name
    QStandardItem *item = templatesModel->itemFromIndex(index);

    m_baseName = index.data(Qt::UserRole+3).toString();
    //baseName can check if an item is selected.
    if (!m_baseName.isEmpty())  {
        ui_choice.kcfg_appName->setFocus(Qt::MouseFocusReason);
    }
    registerField("tempName", this);
    setField("tempName", m_baseName);
    emit completeChanged();
}

#include "choicepage.moc"
