/***************************************************************************
 *   Copyright (C) %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>                            *
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

import QtQuick 1.0;
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.locale 0.1 as Locale

Item {
    id: main;

    property int minimumWidth: 210;
    property int minimumHeight: 210;

    PlasmaCore.Svg {
      //Instantiate a svg instance, set the svg image path
      id: mySvg
      imagePath: plasmoid.file("images", "pairs.svgz")
      
    }
    
    Column {
      spacing: 10;
      id:column
      
      PlasmaCore.SvgItem {
	id: mySvgItem
	width: 180; height: 180
	anchors { horizontalCenter: column.horizontalCenter }
	svg: mySvg //use the svg instanciated above
      }
      
      PlasmaComponents.Label {
	  text: i18n("A column with a SVG and a label")
	  anchors { horizontalCenter: column.horizontalCenter }
	  //the text color is set by the plasma theme
      }
    }
}