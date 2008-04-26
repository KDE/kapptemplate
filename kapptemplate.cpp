/***************************************************************************
 *   Copyright  2008 by Anne-Marie Mahfouf <annma@kde.org>                 *
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

#include <QPixmap>
#include <QRegExpValidator>

#include <kapplication.h>
#include <KLocale>
#include <KDebug>
#include <ktoolinvocation.h>

#include "choicepage.h"
#include "generatepage.h"
#include "kapptemplate.h"
#include "prefs.h"


KAppTemplate::KAppTemplate( QWidget *parent )
    : QWizard()
{
    Q_UNUSED(parent);
    setWindowTitle(i18n("KDE 4 Template Generator"));
    setOption(HaveHelpButton, true);
    connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));
    addPage(new IntroPage);
    addPage(new ChoicePage);
    addPage(new PropertiesPage);
    addPage(new GeneratePage);
}

KAppTemplate::~KAppTemplate()
{
}

void KAppTemplate::showHelp()
{
    KToolInvocation::invokeHelp( "kapptemplate-index", "kapptemplate" );
}


IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(i18n("Introduction"));
    ui_introduction.setupUi(this);
}

PropertiesPage::PropertiesPage(QWidget *parent) //in its own file?
    : QWizardPage(parent)
{
    setTitle(i18n("Set the project properties"));
    ui_properties.setupUi(this);
    //float version = Prefs::appVersion().toFloat();
    ui_properties.kcfg_appVersion->setText(Prefs::appVersion());//TODO appVersion+0.1 if already exists
    ui_properties.kcfg_url->setMode(KFile::Directory);
    ui_properties.kcfg_url->setUrl(Prefs::url());
    ui_properties.kcfg_name->setText(Prefs::name());
    ui_properties.kcfg_email->setText(Prefs::email());

    registerField("author",  ui_properties.kcfg_name);
    registerField("email", ui_properties.kcfg_email);
    registerField("version", ui_properties.kcfg_appVersion);
    registerField("url", ui_properties.kcfg_url->lineEdit());

    //get from emaildefaults [PROFILE_Default]
    connect(ui_properties.kcfg_appVersion, SIGNAL(textChanged(const QString &)), this, SIGNAL(completeChanged()));
    connect(ui_properties.kcfg_url, SIGNAL(textChanged(const QString &)), this, SIGNAL(completeChanged()));
    connect(ui_properties.kcfg_name, SIGNAL(textChanged(const QString &)), this, SIGNAL(completeChanged()));
    connect(ui_properties.kcfg_email, SIGNAL(textChanged(const QString &)), this, SIGNAL(completeChanged()));
    connect(this, SIGNAL(completeChanged()), this, SLOT(saveConfig()));
    // TODO make some fields mandatory?
}

void PropertiesPage::initializePage()
{
    appNameString = field("appName").toString();
    QString message = i18n("Your project name is : %1", appNameString);
    ui_properties.appNameLabel->setText(message);
}

void PropertiesPage::saveConfig()
{
    Prefs::setAppVersion(ui_properties.kcfg_appVersion->text());
    Prefs::setUrl(ui_properties.kcfg_url->url().path());
    Prefs::setName(ui_properties.kcfg_name->text());
    Prefs::setEmail(ui_properties.kcfg_email->text());
    Prefs::setAppName(appNameString);
    Prefs::self()->writeConfig();
}








