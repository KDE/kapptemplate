/*
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

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
    explicit KAppTemplate(QWidget *parent = nullptr);

    /**
     * Default Destructor
     */
    ~KAppTemplate() override;

private Q_SLOTS:
    /**
     * Display KAppTemplate handbook when Help button is clicked
     */
    void showHelp();
};


class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit IntroPage(QWidget *parent = nullptr);

private:
    Ui::introduction ui_introduction;
};

class PropertiesPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit PropertiesPage(QWidget *parent = nullptr);

private:
    Ui::properties ui_properties;
    QString appNameString;

private Q_SLOTS:
    /**
    * Saves all changed fields values in config file
    */
    void saveConfig();

    void initializePage() override;
};

#endif // KAPPTEMPLATE_H
