// SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.1-or-later


import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ScrollablePage {
    id: root

    title: i18nc("@title", "Introduction")

    Component.onCompleted: nextButton.forceActiveFocus();

    ColumnLayout {
        Controls.Label {
            text: i18n("This wizard will help you generate a new project. You will be able to start developing your own software using Qt and KDE technologies from this template.")
            wrapMode: Text.WordWrap

            Layout.fillWidth: true
        }

        Image {
            source: './konqi-app-dev.png'

            Layout.fillWidth: true
            Layout.maximumWidth: Kirigami.Units.gridUnit * 14
            Layout.maximumHeight: Kirigami.Units.gridUnit * 14
            fillMode: Image.PreserveAspectFit
        }
    }

    footer: Controls.ToolBar {
        contentItem: Controls.DialogButtonBox {
            Controls.Button {
                id: nextButton
                text: i18nc("@action:button", "Next")
                icon.name: 'go-next-view-page-symbolic'
                onClicked: Controls.ApplicationWindow.window.pageStack.push(Qt.createComponent('org.kde.kapptemplate', 'ChoicePage'))
            }
        }
    }
}
