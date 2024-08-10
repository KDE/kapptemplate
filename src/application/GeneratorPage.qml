// SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.1-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ScrollablePage {
    id: root

    property Generator generator
    property bool hasError: false
    property bool done: false

    title: i18nc("@title", "Project Generation")

    ColumnLayout {
        spacing: Kirigami.Units.smallSpacing

        Kirigami.Icon {
            visible: root.hasError || root.done
            source: root.hasError ? 'data-error' : (root.done ? 'data-success' : '')

            Layout.preferredWidth: Kirigami.Units.iconSizes.huge
            Layout.preferredHeight: Kirigami.Units.iconSizes.huge
        }

        Controls.ProgressBar {
            id: progressBar

            visible: !root.hasError && !root.done

            Layout.fillWidth: true
        }

        Controls.Label {
            id: messageLabel

            wrapMode: Text.WordWrap

            Layout.fillWidth: true
        }
    }

    Connections {
        target: root.generator

        function onErrorOccurred(errorMessage: string): void {
            root.hasError = true;
            messageLabel.text = errorMessage;
        }

        function onProgressUpdated(progress: int): void {
            progressBar.value = progress / 100;
        }

        function onDone(message: string): void {
            messageLabel.text = message;
            root.done = true;
        }
    }

    footer: Controls.ToolBar {
        contentItem: Controls.DialogButtonBox {
            Controls.Button {
                text: i18nc("@action:button Go to the previous page", "Previous")
                onClicked: Controls.ApplicationWindow.window.pageStack.pop()
                icon.name: 'go-previous-view-page-symbolic'
            }

            Controls.Button {
                text: i18nc("@action:button Close the application", "Close")
                onClicked: Qt.quit()
                icon.name: 'dialog-close-symbolic'
            }
        }
    }
}
