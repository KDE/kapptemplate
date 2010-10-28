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

#include <QDir>
#include <QFileInfo>
#include <QTextCodec>

#include <KDebug>
#include <kmacroexpander.h>
#include <kmessagebox.h>
#include <kstandarddirs.h>
#include <ktempdir.h>
#include <ktar.h>
#include <kzip.h>

#include "kapptemplate.h"
#include "generatepage.h"
#include "prefs.h"

const QString current_year  = QString().setNum(QDate::currentDate().year());

GeneratePage::GeneratePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(i18n("Generating your project"));
    ui_generate.setupUi(this);
}

bool GeneratePage::unpackArchive(const KArchiveDirectory *dir, const QString &dest)
{
    kDebug(9010) << "unpacking dir:" << dir->name() << "to" << dest;
    QStringList entries = dir->entries();
    kDebug(9010) << "entries:" << entries.join(",");

    KTempDir tdir;

    bool ret = true;

    //create path were we want copy files to
    if(!QDir::root().mkpath(dest)){
        KMessageBox::sorry(0, i18n("%1 cannot be created.", dest));
        return false;
    }

    int progress = 0;

    foreach (const QString &entry, entries)
    {
        progress++;
        ui_generate.progressBar->setValue( (progress / entries.size()) * 100);
	//don't copy .kdevtemplate 
        if (entry.endsWith(".kdevtemplate"))
            continue;
	if (entry == templateName+".png")
	    continue;
        if (dir->entry(entry)->isDirectory())  {
            const KArchiveDirectory *file = (KArchiveDirectory *)dir->entry(entry);
            QString newdest = dest+"/"+file->name();
            if( !QFileInfo( newdest ).exists() )  {
                QDir::root().mkdir( newdest  );
            }
            ret |= unpackArchive(file, newdest);
        }
        else if (dir->entry(entry)->isFile())  {
            const KArchiveFile *file = (KArchiveFile *)dir->entry(entry);
            file->copyTo(tdir.name());
            QString destName = dest + '/' + file->name();
	    if (!destName.contains("/icons/")) {
		if (!copyFile(QDir::cleanPath(tdir.name()+'/'+file->name()),
                    KMacroExpander::expandMacros(destName, m_variables))) {
		    KMessageBox::sorry(0, i18n("The file %1 cannot be created.", dest));
		    feedback.append(i18n("\n\nThe file %1 cannot be created.", dest));
		    ui_generate.label->setText(feedback);
		    return false;
		}
	    }
	    else  {
		//do not parse .png but parse filemanes for placeholders
		if (!QFile(QDir::cleanPath(tdir.name()+'/'+file->name())).copy(KMacroExpander::expandMacros(destName, m_variables))) {
		    KMessageBox::sorry(0, i18n("The file %1 cannot be created.", dest));
		    feedback.append(i18n("\n\nThe file %1 cannot be created.", dest));
		    ui_generate.label->setText(feedback);
		    return false;
		}
	    kDebug() << "after copying.... " << endl;
	    }
        }
    }
    tdir.unlink();
    return ret;
}

bool GeneratePage::copyFile(const QString &source, const QString &dest)
{
    kDebug(9010) << "copy:" << source << "to" << dest;
    QFile inputFile(source);
    QFile outputFile(dest);

    QFileInfo temp(source);

    if (inputFile.open(QFile::ReadOnly) && outputFile.open(QFile::WriteOnly))
    {
        if(temp.suffix().compare("png",Qt::CaseInsensitive) == 0)
        {
            QDataStream input(&inputFile);
            QDataStream output(&outputFile);

            while(!input.atEnd())  {
                qint8 t;
                input >> t;
                output << t;
            }
        }  else  {
            QTextStream input(&inputFile);
            input.setCodec(QTextCodec::codecForName("UTF-8"));
            QTextStream output(&outputFile);
            output.setCodec(QTextCodec::codecForName("UTF-8"));
    
            while(!input.atEnd())  {
                QString line = input.readLine();
    
                output << KMacroExpander::expandMacros(line, m_variables) << "\n";
            }
        }

        struct stat fmode;
        ::fstat(inputFile.handle(), &fmode);
        ::fchmod(outputFile.handle(), fmode.st_mode);

        return true;
    }  else  {
        inputFile.close();
        outputFile.close();
        return false;
    }
}

void GeneratePage::initializePage()
{
    feedback = i18n("Generation Progress\n");
    ui_generate.label->setText(feedback);
    templateName = field("tempName").toString();
    if (templateName.isEmpty())  {
	templateName = "kde4";
    }
    QString templateArchive = KGlobal::dirs()->findResource("data", QString("kdevappwizard/templates/%1.zip").arg(templateName));
    if( templateArchive.isEmpty() )  {
        templateArchive = KGlobal::dirs()->findResource("data", QString("kdevappwizard/templates/%1.tar.bz2").arg(templateName));
    }
    //create dir where template project will be copied
    QString appName = field("appName").toString();
    QString version = field("version").toString();
    KUrl dest(field("url").toString()+"/"+appName.toLower());
    m_variables.clear();
    m_variables["CURRENT_YEAR"]=current_year;
    m_variables["APPNAME"] = appName;
    m_variables["APPNAMEUC"] = appName.toUpper();
    m_variables["APPNAMELC"] = appName.toLower();
    m_variables["PROJECTDIRNAME"] = appName.toLower();
    m_variables["APPNAMEFU"] = appName.replace(0, 1, appName.toUpper().at(0));
    m_variables["AUTHOR"] = field("author").toString();
    m_variables["EMAIL"] = field("email").toString();
    m_variables["VERSION"] = version;
    m_variables["VERSIONCONTROLPLUGIN"] = version;
    m_variables["PROJECTDIRNAME"] = appName.toLower()+"-"+version;// TODO what for? change "dest" to that?

    KArchive* arch = 0;
    if( templateArchive.endsWith(".zip") )  {
        arch = new KZip(templateArchive);
    }  else  {
        arch = new KTar(templateArchive, "application/x-bzip");
    }
    if (arch->open(QIODevice::ReadOnly))  {
	if( !QFileInfo( dest.toLocalFile() ).exists() )  {
                QDir::root().mkdir( dest.toLocalFile() );
        }
        unpackArchive(arch->directory(), dest.toLocalFile());
    }
    delete arch;

    feedback.append(i18n("Succeeded.\n"));
    ui_generate.label->setText(feedback);

    QString resume;
    QString url = field("url").toString();
    resume = i18n("Your project name is: <b>%1</b>, based on the %2 template.<br />", appName, templateName);
    resume.append(i18n("Version: %1 <br /><br />", version));
    resume.append(i18n("Installed in: %1 <br /><br />", url));
    resume.append(i18n("You will find a README in your project folder <b>%1</b><br /> to help you get started with your project.", url+'/'+appName.toLower()));
    ui_generate.summaryLabel->setText(resume);
}

#include "generatepage.moc"
