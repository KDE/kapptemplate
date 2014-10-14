/***************************************************************************
 *   Copyright (C) %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>                 *
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

#ifndef %{APPNAMEUC}PART_H
#define %{APPNAMEUC}PART_H

#include <kparts/part.h>

class QWidget;
class QPainter;
class KUrl;
class QTextEdit;
class KAboutData;
class KAction;

/**
 * This is a "Part".  It does all the real work in a KPart
 * application.
 *
 * @short Main Part
 * @author %{AUTHOR} <%{EMAIL}>
 * @version ${APP_VERSION}
 */
class %{APPNAME}Part : public KParts::ReadWritePart
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    %{APPNAME}Part(QWidget *parentWidget, QObject *parent, const QVariantList &);

    /**
     * Destructor
     */
    virtual ~%{APPNAME}Part();

    /**
     * This is a virtual function inherited from KParts::ReadWritePart.
     * A shell will use this to inform this Part if it should act
     * read-only
     */
    virtual void setReadWrite(bool rw);

    /**
     * Reimplemented to disable and enable Save action
     */
    virtual void setModified(bool modified);

    static KAboutData *createAboutData();

protected:
    /**
     * This must be implemented by each part
     */
    virtual bool openFile();

    /**
     * This must be implemented by each read-write part
     */
    virtual bool saveFile();
    KAction *save;

protected slots:
    void fileSaveAs();

private:
    QTextEdit *m_widget;
};

#endif // %{APPNAMEUC}PART_H
