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
        
        
Kirigami.ScrollablePage {
    id: root
    title: i18n("Saved colors")
    ListView {
        model: SavedColors
        
        delegate: Kirigami.AbstractListItem {
            background: Rectangle {
                anchors.fill: parent
                color: backgroundColor
            }
            
            ColumnLayout {
                Text {
                    Layout.fillWidth: true
                    font.pointSize: 30
                    text: "Lorem Impsum"
                    color: textColor
                }
                Text {
                    Layout.fillWidth: true
                    font.pointSize: 20
                    text: "Lorem Impsum reroie joirej je roje oijre oijeo"
                    wrapMode: Text.WordWrap
                    color: textColor
                }
                
                RowLayout {
                    Layout.fillWidth: true
                    Text {
                        Layout.fillWidth: true
                        text: i18n("Text: %1", textColor)
                        color: textColor
                    }
                    Text {
                        Layout.fillWidth: true
                        text: i18n("Background: %1", backgroundColor)
                        color: textColor
                    }
                }
            }
        }
    }
}
