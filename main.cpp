/***************************************************************************
 *   Copyright  2008 by Anne-Marie Mahfouf <annma@kde.org>                 *
 *   Copyright  2008 by Beat Wolf          <asraniel@fryx.ch>              *
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

#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>
#include <kapplication.h>
#include <kstandarddirs.h>

#include "kapptemplate.h"

static const char description[] =
    I18N_NOOP("KAppTemplate is a KDE 4 project template generator");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    KAboutData about("kapptemplate", 0, ki18n("KAppTemplate"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2008 Anne-Marie Mahfouf"),KLocalizedString(), 0, "submit@bugs.kde.org");
    about.addAuthor( ki18n("Anne-Marie Mahfouf"), KLocalizedString(), "annma AT kde DOT org");
    about.addAuthor( ki18n("Sean Wilson"), ki18n("Icons from Oxygen Team icons"), "suseux AT googlemail DOT com");
    
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    KStandardDirs* dirs = KGlobal::dirs();
    dirs->addResourceType( "apptemplates", "data", "kdevappwizard/templates/" );
    dirs->addResourceType( "apptemplate_descriptions", "data", "kdevappwizard/template_descriptions/" );
    dirs->addResourceType( "apptemplate_previews", "data", "kdevappwizard/template_previews/" );

    KAppTemplate appTemplate(0);
    appTemplate.show();


    return app.exec();
} 
