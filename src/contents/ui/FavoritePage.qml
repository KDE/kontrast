/**
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-LicenseRef: GPL-3.0-or-later
 */

import QtQuick 2.1
import org.kde.kirigami 2.14 as Kirigami
import QtQuick.Controls 2.14 as QQC2
import QtQuick.Window 2.14
import QtQuick.Layouts 1.14
import org.kde.kontrast.private 1.0
import org.kde.kquickcontrolsaddons 2.0 as QtExtra
        
        
Kirigami.ScrollablePage {
    id: root
    title: i18n("Saved colors")
    property bool isMobile: Window.width <= Kirigami.Units.gridUnit * 30
    ListView {
        model: ColorStore
        QtExtra.Clipboard {
            id: clipboard
        }
        
        spacing: Kirigami.Units.smallSpacing
        
        delegate: Kirigami.AbstractListItem {
            background: Rectangle {
                anchors.fill: parent
                color: model.backgroundColor
            }
            
            RowLayout {
                ColumnLayout {
                    Text {
                        Layout.fillWidth: true
                        font.pointSize: 22
                        text: "Lorem Impsum"
                        color: model.textColor
                    }

                    Text {
                        Layout.fillWidth: true
                        font.pointSize: 16
                        text: "Lorem Impsum reroie joirej je roje oijre oijeo"
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
                                onClicked: copyTex();
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
                                onClicked: copyBackground();
                            }
                        }
                    }
                }
                
                QQC2.Button {
                    text: i18n("Remove")
                    onClicked: {
                        ColorStore.removeColor(model.index)
                    }
                }
            }
        }
    }
    
    function copyBackground() {
        clipboard.content = Kontrast.backgroundColor;
        inlineMessage.text = i18n("Background color copied to clipboard");
        inlineMessage.visible = true;
        timer.interval = Kirigami.Units.longDuration
        timer.running = true;
    }
    
    function copyText() {
        clipboard.content = Kontrast.textColor;
        inlineMessage.text = i18n("Text color copied to clipboard");
        inlineMessage.visible = true;
        timer.interval = Kirigami.Units.longDuration
        timer.running = true;
    }
    
    footer: Kirigami.InlineMessage {
        id: inlineMessage
        type: Kirigami.MessageType.Information
        text: i18n("Color copied to clipboard")
        
        Timer {
            id: timer
            interval: Kirigami.Units.longDuration
            onTriggered: inlineMessage.visible = false
        }
    }
}
