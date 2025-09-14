/**
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Window
import QtQuick.Layouts
import org.kde.kirigami as Kirigami
import org.kde.kontrast

Kirigami.ScrollablePage {
    id: root

    property bool isMobile: Window.width <= Kirigami.Units.gridUnit * 30
    property Kirigami.Action contrastChecker

    title: i18nc("@title:menu", "Favorite Colors")

    ListView {
        id: listview
        model: ColorStore

        spacing: Kirigami.Units.smallSpacing

        delegate: QQC2.ItemDelegate {
            id: delegate

            required property int index
            required property color backgroundColor
            required property color textColor

            width: ListView.view.width

            background: Rectangle {
                color: delegate.backgroundColor
            }

            contentItem: ColumnLayout {
                id: layout

                spacing: Kirigami.Units.largeSpacing

                Kirigami.Heading {
                    level: 3
                    text: "Lorem Ipsum"
                    color: delegate.textColor

                    Layout.fillWidth: true

                    QQC2.Button {
                        anchors.right: parent.right
                        icon.name: "edit-delete-remove"

                        onClicked: {
                            ColorStore.removeColor(delegate.index)
                        }

                        QQC2.ToolTip.text: i18nc("@action:tooltip", "Remove")
                        QQC2.ToolTip.visible: hovered
                        QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
                    }
                }

                Text {
                    Layout.fillWidth: true
                    text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque et dolor velit. Morbi elementum libero non vehicula porta. Suspendisse potenti. Suspendisse eu sapien lectus."
                    wrapMode: Text.WordWrap
                    color: delegate.textColor
                }

                RowLayout {
                    Layout.fillWidth: true
                    QQC2.Button {
                        text: i18nc("@action:button", "Text: %1", delegate.textColor)
                        icon.source: "edit-copy"
                        onClicked: root.copyText(delegate.textColor)
                    }
                    QQC2.Button {
                        text: i18nc("@action:button", "Background: %1", delegate.backgroundColor)
                        icon.source: "edit-copy"
                        onClicked: root.copyBackground(delegate.backgroundColor)
                    }
                }

                QQC2.Button {
                    text: i18nc("@action:button", "Apply")
                    icon.name: "dialog-ok-apply"
                    onClicked: {
                        Kontrast.textColor = delegate.textColor
                        Kontrast.backgroundColor = delegate.backgroundColor
                        root.contrastChecker.trigger()
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

    function copyBackground(colorText: color): void {
        copyColorTextToClipboard(colorText, i18nc("@info:inline", "Background color copied to clipboard"))
    }

    function copyText(colorText: color): void {
        copyColorTextToClipboard(colorText, i18nc("@info:inline", "Text color copied to clipboard"))
    }

    footer: Kirigami.InlineMessage {
        id: inlineMessage
        type: Kirigami.MessageType.Information
        position: Kirigami.InlineMessage.Footer
        text: i18nc("@info:inline", "Color copied to clipboard")
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
