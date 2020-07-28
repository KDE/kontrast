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
import QtQuick.Dialogs 1.0

Kirigami.ScrollablePage {
    id: mainPage
    property bool isMobile: Window.width <= Kirigami.Units.gridUnit * 30
    
    title: i18n("kontrast")
    background: Rectangle {
        color: Kontrast.backgroundColor
    }
    
    ColumnLayout {
        ColorDialog {
            id: colorDialog
            property var target: "textColor";
            title: "Please choose a color"
            onAccepted: {
                if (target === "textColor") {
                    Kontrast.textColor = colorDialog.color;
                } else {
                    Kontrast.backgroundColor = colorDialog.color;
                }
            }
        }
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
                
                QQC2.TextField {
                    text: Kontrast.textColor
                    font.pointSize: 35
                    color: Kontrast.textColor
                    background: Rectangle { color: Kontrast.backgroundColor }
                    onEditingFinished: Kontrast.textColor = text
                    
                    QQC2.Button {
                        icon.name: "color-picker"
                        anchors {
                            left: parent.right
                            verticalCenter: parent.verticalCenter
                        }
                        onClicked: {
                            colorDialog.color = Kontrast.textColor
                            colorDialog.target = "textColor";
                            colorDialog.visible = true;
                        }
                    }
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
            
                QQC2.TextField {
                    text: Kontrast.backgroundColor
                    font.pointSize: 35
                    color: Kontrast.textColor
                    background: Rectangle { color: Kontrast.backgroundColor }
                    onEditingFinished: Kontrast.backgroundColor = text
                    QQC2.Button {
                        icon.name: "color-picker"
                        anchors {
                            left: parent.right
                            verticalCenter: parent.verticalCenter
                        }
                        onClicked: {
                            colorDialog.color = Kontrast.backgroundColor;
                            colorDialog.target = "backgroundColor";
                            colorDialog.visible = true;
                        }
                    }
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
                icon.name: "reverse"
            }
            
            QQC2.Button {
                text: i18n("Random")
                onClicked: Kontrast.random()
                icon.name: "randomize"
            }
            
            QQC2.Button {
                text: i18n("Save color")
                icon.name: "favorite"
                onClicked: if (!ColorStore.addColor("Lorem Ipsum", Kontrast.textColor, Kontrast.backgroundColor)) {
                    applicationWindow().showPassiveNotification(i18n("Failed to save color"))
                }
            }
        }
        
        
        ShaderEffect {
            height: 300
            width: 300
            property point u_resolution: Qt.point(width, height)
            fragmentShader: "#ifdef GL_ES
precision mediump float;
#endif

#define TWO_PI 6.28318530718

uniform vec2 u_resolution;

//  Function from Inigo Quiles
//  https://www.shadertoy.com/view/MsS3Wc
vec3 hsb2rgb(in vec3 c)
{
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix( vec3(1.0), rgb, c.y);
}

void main()
{
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec3 color = vec3(0.0);

    // Use polar coordinates instead of cartesian
    vec2 toCenter = vec2(0.5)-st;
    float angle = atan(toCenter.y,toCenter.x);
    float radius = length(toCenter)*2.0;
    
    vec2 center = vec2(u_resolution.x/2., u_resolution.y/2.);
    float radius2 = u_resolution.x/2.;
    vec2 position = gl_FragCoord.xy - center;
    
    if (length(position) <= radius2) {
        // Map the angle (-PI to PI) to the Hue (from 0 to 1)
        // and the Saturation to the radius
        color = hsb2rgb(vec3((angle/TWO_PI)+0.5,radius,1.0));
        gl_FragColor = vec4(color,1.0);
    } else {
        gl_FragColor = vec4(vec3(1.), 0.);
    }
}";
        }
    }
}
