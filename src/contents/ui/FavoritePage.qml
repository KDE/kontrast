/**
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.1
import org.kde.kirigami 2.12 as Kirigami
import QtQuick.Controls 2.14 as QQC2
import QtQuick.Window 2.14
import QtQuick.Layouts 1.14
import org.kde.kontrast.private 1.0

Kirigami.ScrollablePage {
    id: root
    title: i18n("Favorite colors")
    property bool isMobile: Window.width <= Kirigami.Units.gridUnit * 30
    ListView {
        id: listview
        model: ColorStore

        spacing: Kirigami.Units.smallSpacing

        delegate: QQC2.ItemDelegate {

            width: ListView.view.width

            background: Rectangle {
                anchors.fill: parent
                color: model.backgroundColor
            }

            contentItem: ColumnLayout {
                id: layout
                Kirigami.Heading {
                    Layout.fillWidth: true
                    level: 3
                    text: "Lorem Impsum"
                    color: model.textColor

                    QQC2.Button {
                        anchors.right: parent.right
                        icon.name: "edit-delete-remove"
                        QQC2.ToolTip.text: i18n("Remove")
                        QQC2.ToolTip.visible: hovered
                        onClicked: {
                            ColorStore.removeColor(model.index)
                        }
                    }
                }

                Text {
                    Layout.fillWidth: true
                    text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque et dolor velit. Morbi elementum libero non vehicula porta. Suspendisse potenti. Suspendisse eu sapien lectus."
                    wrapMode: Text.WordWrap
                    color: model.textColor
                }
                
                RowLayout {
                    Layout.fillWidth: true
                    QQC2.Button {
                        text: i18n("Text: %1", model.textColor)
                        icon.source: "edit-copy"
                        onClicked: copyText(model.textColor)
                    }
                    QQC2.Button {
                        text: i18n("Background: %1", model.backgroundColor)
                        icon.source: "edit-copy"
                        onClicked: copyBackground(model.backgroundColor)
                    }
                }
            }
        }
    }

    // Workaround for QTBUG-21989
    TextInput {
       id: clipboard
       visible: false
       property string content
       onContentChanged: {
           text = content
           selectAll()
           copy()
       }
    }

    function copyColorTextToClipboard(colorText, passiveMessageText) {
        clipboard.content = colorText
        inlineMessage.showPassive(passiveMessageText)
    }
    
    function copyBackground(colorText) {
        copyColorTextToClipboard(colorText, i18n("Background color copied to clipboard"))
    }
    
    function copyText(colorText) {
        copyColorTextToClipboard(colorText, i18n("Text color copied to clipboard"))
    }
    
    footer: Kirigami.InlineMessage {
        id: inlineMessage
        type: Kirigami.MessageType.Information
        position: Kirigami.InlineMessage.Footer
        text: i18n("Color copied to clipboard")
        visible: false
        
        Timer {
            id: timer
            interval: Kirigami.Units.humanMoment
            onTriggered: inlineMessage.visible = false
        }

        function showPassive(message) {
            text = message
            visible = true
            timer.running = true
        }
    }
}
