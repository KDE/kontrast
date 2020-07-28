/**
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-LicenseRef: GPL-3.0-or-later
 */

import QtQuick 2.1
import org.kde.kirigami 2.11 as Kirigami
import QtQuick.Controls 2.14 as QQC2
import QtQuick.Window 2.14
import QtQuick.Layouts 1.14
import org.kde.kontrast.private 1.0

Kirigami.ScrollablePage {
    id: mainPage
    property bool isMobile: Window.width <= Kirigami.Units.gridUnit * 30
    
    title: i18n("kontrast")
    background: Rectangle {
        color: Kontrast.backgroundColor
    }
    
    ColumnLayout {
        Text {
            font.pointSize: 45
            font.bold: true
            text: "Aa " + Kontrast.contrast.toFixed(2)
            color: Kontrast.textColor
            Layout.fillWidth: true
        }
        
        Text {
            font.pointSize: mainPage.isMobile ? 12 : 18
            font.bold: true
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            text: i18n("Contrast is the difference in luminance or color that makes an object (or its representation in an image or display) distinguishable. In visual perception of the real world, contrast is determined by the difference in the color and brightness of the object and other objects within the same field of view.")
            color: Kontrast.textColor
        }
        
        GridLayout {
            Layout.fillWidth: true
            columns: mainPage.isMobile ? 1 : 3
            rowSpacing: Kirigami.Units.gridUnit
            
            ColumnLayout {
                Layout.fillWidth: true
                
                Text {
                    Layout.topMargin: Kirigami.Units.largeSpacing
                    text: i18n("Text")
                    color: Kontrast.displayTextColor
                }
                
                TextEdit {
                    text: Kontrast.textColor
                    font.pointSize: 35
                    color: Kontrast.textColor
                    Layout.fillWidth: true
                }
                
                Text {
                    Layout.topMargin: Kirigami.Units.largeSpacing
                    text: i18n("Hue %1°", Kontrast.textHue)
                    color: Kontrast.displayTextColor
                }
                
                QQC2.Slider {
                    from: 0
                    value: Kontrast.textHue
                    to: 360
                    onMoved: Kontrast.textHue = value
                    Layout.fillWidth: true
                }
                
                Text {
                    Layout.topMargin: Kirigami.Units.largeSpacing
                    text: i18n("Saturation %1", (Kontrast.textSaturation / 255))
                    color: Kontrast.displayTextColor
                }
                
                QQC2.Slider {
                    from: 0
                    value: Kontrast.textSaturation
                    to: 255
                    onMoved: Kontrast.textSaturation = value
                    Layout.fillWidth: true
                }
                
                Text {
                    Layout.topMargin: Kirigami.Units.largeSpacing
                    text: i18n("Lightness %1", (Kontrast.textLightness / 255))
                    color: Kontrast.displayTextColor
                }
                
                QQC2.Slider {
                    from: 0
                    value: Kontrast.textLightness
                    to: 255
                    onMoved: Kontrast.textLightness = value
                    Layout.fillWidth: true
                }
            }
            
            Kirigami.Separator {
                visible: mainPage.isMobile
                Layout.fillWidth: true
                color: Kontrast.displayTextColor
            }
            
            ColumnLayout {
                Layout.fillWidth: true
                
                Text {
                    Layout.topMargin: Kirigami.Units.largeSpacing
                    text: i18n("Background")
                    color: Kontrast.displayTextColor
                }
            
                TextEdit {
                    text: Kontrast.backgroundColor
                    font.pointSize: 35
                    color: Kontrast.textColor
                    Layout.fillWidth: true
                }
                
                Text {
                    Layout.topMargin: Kirigami.Units.largeSpacing
                    text: i18n("Hue %1°", Kontrast.backgroundHue)
                    color: Kontrast.displayTextColor
                }
                
                QQC2.Slider {
                    from: 0
                    value: Kontrast.backgroundHue
                    to: 360
                    onMoved: Kontrast.backgroundHue = value
                    Layout.fillWidth: true
                }
                
                Text {
                    Layout.topMargin: Kirigami.Units.largeSpacing
                    text: i18n("Saturation %1", (Kontrast.backgroundSaturation / 255))
                    color: Kontrast.displayTextColor
                }
                
                QQC2.Slider {
                    from: 0
                    value: Kontrast.backgroundSaturation
                    to: 255
                    onMoved: Kontrast.backgroundSaturation = value
                    Layout.fillWidth: true
                }
                
                Text {
                    Layout.topMargin: Kirigami.Units.largeSpacing
                    text: i18n("Saturation %1", (Kontrast.backgroundLightness / 255))
                    color: Kontrast.displayTextColor
                }
                
                QQC2.Slider {
                    from: 0
                    value: Kontrast.backgroundLightness
                    to: 255
                    onMoved: Kontrast.backgroundLightness = value
                    Layout.fillWidth: true
                }
            }
        }
        
        RowLayout {
            Layout.topMargin: Kirigami.Units.gridUnit * 2
            QQC2.Button {
                text: i18n("Reverse")
                onClicked: Kontrast.reverse()
            }
            
            QQC2.Button {
                text: i18n("Random")
                onClicked: Kontrast.random()
            }
            
            QQC2.Button {
                text: i18n("Save color")
                icon.name: "favorite"
                onClicked: Kontrast.savedColors.addColor(Kontrast.textColor, Kontrast.backgroundColor);
            }
        }
    }
}
