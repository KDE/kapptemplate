// SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.1-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import QtQuick.Dialogs
import org.kde.kitemmodels
import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as FormCard

FormCard.FormCardPage {
    id: root

    title: i18nc("@title", "Configure")

    property string templateName
    property string displayName

    Generator {
        id: generator
    }

    FormCard.FormHeader {
        title: i18nc("@title:group", "General")
    }

    FormCard.FormCard {
        FormCard.FormTextFieldDelegate {
            id: nameField

            label: i18nc("@label:textbox", "Name:")
            validator: RegularExpressionValidator {
                regularExpression: /[a-zA-Z0-9_]*/
            }
            focus: true
            text: generator.name
            onTextChanged: generator.name = text
        }

        FormCard.FormDelegateSeparator {}

        FormCard.FormButtonDelegate {
            text: i18nc("@label:textbox", "Location:")
            description: generator.location.length > 0 ? generator.location : i18nc("@info:placeholder", "No folder selected")
            onClicked: folderDialog.open()

            FolderDialog {
                id: folderDialog
                selectedFolder: 'file://' + generator.location
                onAccepted: generator.location = selectedFolder.toString().substring(7)
            }
        }
    }

    FormCard.FormHeader {
        title: i18nc("@title:group", "Metadata")
    }

    FormCard.FormCard {
        FormCard.FormTextFieldDelegate {
            label: i18nc("@label:textbox", "Version:")
            text: generator.version
            onTextChanged: generator.version = text
        }

        FormCard.FormDelegateSeparator {}

        FormCard.FormTextFieldDelegate {
            label: i18nc("@label:textbox", "Author name:")
            text: generator.authorName
            onTextChanged: generator.authorName = text
        }

        FormCard.FormDelegateSeparator {}

        FormCard.FormTextFieldDelegate {
            label: i18nc("@label:textbox", "Author email:")
            text: generator.authorEmail
            onTextChanged: generator.authorEmail = text
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
                text: i18nc("@action:button Generate the application", "Generate")
                enabled: generator.location.length > 0 && generator.name.length > 0
                onClicked: {
                    Controls.ApplicationWindow.window.pageStack.push(Qt.createComponent('org.kde.kapptemplate', 'GeneratorPage'), {
                        generator: generator,
                    });
                    generator.startGeneration(root.templateName, root.displayName);
                }
                icon.name: 'dialog-ok-symbolic'
            }
        }
    }
}
