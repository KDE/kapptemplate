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

#ifndef KAPPTEMPLATE_H
#define KAPPTEMPLATE_H

#include <QWizard>

#include "ui_introduction.h"
#include "ui_properties.h"

/**
 * This class serves as the main window for KAppTemplate.  It is a wizard-like
 * application.
 *
 * @short Main window class
 * @author Anne-Marie Mahfouf <annma@kde.org>
 * @version 0.1
 */

class KAppTemplate : public QWizard
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    KAppTemplate(QWidget *parent );

    /**
     * Default Destructor
     */
    virtual ~KAppTemplate();

private slots:
    /**
     * Display KAppTemplate handbook when Help button is clicked
     */
    void showHelp();
};


class IntroPage : public QWizardPage
{
    Q_OBJECT

    public:
	IntroPage(QWidget *parent = 0);
    private:
	Ui::introduction ui_introduction;
};

class PropertiesPage : public QWizardPage
{
    Q_OBJECT

    public:
	PropertiesPage(QWidget *parent = 0);

    private:
	Ui::properties ui_properties;
	QString appNameString;

    private slots:
	/**
	* Saves all changed fields values in config file
	*/
	void saveConfig();

    	void initializePage();

    Q_SIGNALS:
	/**
	* Emitted when the text in any field changes.
	*/
	void completeChanged();
};



#endif // _KAPPTEMPLATE_H_
