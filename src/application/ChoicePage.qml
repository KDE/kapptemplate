// SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.1-or-later

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import QtQuick.Dialogs
import org.kde.kitemmodels
import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.treeview as Tree
import org.kde.kirigamiaddons.delegates as Delegates

Kirigami.Page {
    id: root

    title: i18nc("@title", "Choose Template")

    padding: 0

    Component.onCompleted: {
        appTemplatesModel.refresh();
        choiceView.forceActiveFocus();
    }

    actions: Kirigami.Action {
        text: i18nc("@action:intoolbar", "Install Template From File")
        icon.name: 'application-x-archive'
        onTriggered: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        nameFilters: [i18nc("file dialog name filter", "Archive Files (*.tar.bz2 *.zip)")]
        fileMode: FileDialog.OpenFiles
        onAccepted: appTemplatesModel.loadFromFiles(selectedFiles.map((file) => file.toString().substring(7)))
    }

    contentItem: Controls.SplitView {
        Controls.ScrollView {
            background: Rectangle {
                Kirigami.Theme.colorSet: Kirigami.Theme.View
                color: Kirigami.Theme.backgroundColor
            }

            contentItem: ListView {
                id: choiceView

                clip: true
                currentIndex: -1

                model: KDescendantsProxyModel {
                    id: treeModel

                    model: AppTemplatesModel {
                        id: appTemplatesModel
                    }
                }

                delegate: Delegates.RoundedTreeDelegate {
                    id: delegate

                    required property string name
                    required property string descriptionFile
                    required property string pictureName
                    required property string baseName

                    text: name

                    onClicked: if (baseName.length > 0) {
                        if (ListView.isCurrentItem) {
                            nextButton.clicked();
                        } else {
                            choiceView.currentIndex = index;
                        }
                    } else {
                        treeModel.toggleChildren(delegate.index);
                    }
                }
            }

            Controls.SplitView.minimumWidth: Kirigami.Units.gridUnit * 15
        }

        Kirigami.ScrollablePage {
            id: scrollview

            leftPadding: Kirigami.Units.largeSpacing
            topPadding: Kirigami.Units.largeSpacing
            bottomPadding: Kirigami.Units.largeSpacing
            rightPadding: Kirigami.Units.largeSpacing

            ColumnLayout {
                spacing: Kirigami.Units.smallSpacing

                Kirigami.Heading {
                    text: choiceView.currentItem && choiceView.currentItem.name.length > 0 ? choiceView.currentItem.name : i18nc("@title", "No Template Selected")
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Image {
                    source: choiceView.currentItem ? 'image://preview/' + choiceView.currentItem.pictureName + '/' + choiceView.currentItem.baseName : ''
                    Layout.fillWidth: true
                    Layout.maximumHeight: implicitHeight * scrollview.availableWidth / implicitWidth
                }

                Controls.Label {
                    text: choiceView.currentItem && choiceView.currentItem.descriptionFile.length > 0 ? choiceView.currentItem.descriptionFile : ''
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }

    footer: Controls.ToolBar {
        contentItem: Controls.DialogButtonBox {
            Controls.Button {
                text: i18nc("@action:button", "Previous")
                onClicked: Controls.ApplicationWindow.window.pageStack.pop()
                icon.name: 'go-previous-view-page-symbolic'
            }

            Controls.Button {
                id: nextButton

                enabled: choiceView.currentItem?.baseName.length > 0
                text: i18nc("@action:button", "Next")
                onClicked: Controls.ApplicationWindow.window.pageStack.push(Qt.createComponent('org.kde.kapptemplate', 'ConfigurePage'), {
                    templateName: choiceView.currentItem.baseName,
                    displayName: choiceView.currentItem.name,
                })
                icon.name: 'go-next-view-page-symbolic'
            }
        }
    }
}
