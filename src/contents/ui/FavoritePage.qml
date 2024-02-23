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
        Clipboard {
            id: clipboard
        }

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
                }

                Text {
                    Layout.fillWidth: true
                    text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque et dolor velit. Morbi elementum libero non vehicula porta. Suspendisse potenti. Suspendisse eu sapien lectus."
                    wrapMode: Text.WordWrap
                    color: model.textColor
                }

                Text {
                    text: i18n("Text: %1", model.textColor)
                    color: model.textColor
                    MouseArea {
                        anchors.fill: parent
                        onClicked: copyText();
                    }
                    Kirigami.Icon {
                        anchors.left: parent.right
                        height: parent.height
                        width: parent.height
                        source: "edit-copy"
                        color: model.textColor
                        MouseArea {
                            anchors.fill: parent
                            onClicked: copyText(model.textColor);
                        }
                    }
                }

                Text {
                    text: i18n("Background: %1", model.backgroundColor)
                    color: model.textColor

                    MouseArea {
                        anchors.fill: parent
                        onClicked: copyBackground();
                    }
                    Kirigami.Icon {
                        anchors.left: parent.right
                        height: parent.height
                        width: parent.height
                        source: "edit-copy"
                        color: model.textColor
                        MouseArea {
                            anchors.fill: parent
                            onClicked: copyBackground(model.backgroundColor);
                        }
                    }
                }

                QQC2.Button {
                    text: i18n("Remove")
                    Layout.topMargin: Kirigami.Units.largeSpacing
                    onClicked: {
                        ColorStore.removeColor(model.index)
                    }
                }
            }
        }
    }
    
    function copyBackground(colorText) {
        clipboard.content = colorText;
        inlineMessage.text = i18n("Background color copied to clipboard");
        inlineMessage.visible = true;
        timer.interval = Kirigami.Units.longDuration
        timer.running = true;
    }
    
    function copyText(colorText) {
        clipboard.content = colorText;
        inlineMessage.text = i18n("Text color copied to clipboard");
        inlineMessage.visible = true;
        timer.interval = Kirigami.Units.longDuration
        timer.running = true;
    }
    
    footer: Kirigami.InlineMessage {
        id: inlineMessage
        type: Kirigami.MessageType.Information
        position: Kirigami.InlineMessage.Footer
        text: i18n("Color copied to clipboard")
        
        Timer {
            id: timer
            interval: Kirigami.Units.longDuration
            onTriggered: inlineMessage.visible = false
        }
    }
}
