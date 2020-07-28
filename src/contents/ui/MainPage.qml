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
    
    title: i18n("Kontrast %1", Kontrast.contrast.toFixed(2))
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
            text: i18n("Contrast ratio: %1", Kontrast.contrast.toFixed(2))
            
            color: Kontrast.textColor
            Layout.fillWidth: true
        }
        Text {
            font.pointSize: mainPage.isMobile ? 12 : 18
            font.bold: true
            color: Kontrast.textColor
            Layout.fillWidth: true
            text: (Kontrast.contrast > 7 ? i18n("Perfect for normal and large text") : Kontrast.contrast > 4.5 ? i18n("Perfect for large text and good for normal text") : Kontrast.contrast > 3.0 ? i18n("Good for large text and bad for normal text") : i18n("Bad for large and normal text"))
        }
        
        Text {
            font.pointSize: mainPage.isMobile ? 12 : 18
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
                text: i18n("Inverse")
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
        
  /*      ShaderEffect {
            id: colorWheel
            height: 300
            width: 300
            property point i_resolution: Qt.point(width, height)
            property color i_background: Kontrast.backgroundColor
            property point i_mouse: Qt.point(-1, -1)
            property point i_mouse2: Qt.point(-1, -1)
            property real i_hue: Math.PI * Kontrast.textHue / 180.0
            property color i_color: Kontrast.textColor
            
            fragmentShader: "
                #define M_PI 3.1415926535897932384626433832795
                varying highp vec2 qt_TexCoord0;
                uniform vec2 i_resolution;
                uniform vec2 i_mouse;
                uniform vec2 i_mouse2;
                uniform vec4 i_background;
                uniform vec4 i_color;
                uniform float i_hue;

                //    0  1  2  3  4  5 
                // R  1  1  0  0  0  1
                // G  0  1  1  1  0  0
                // B  0  0  0  1  1  1
                vec3 getHueColor(vec2 pos)
                {
                    float theta = 3.0 + 3.0 * atan(pos.x, pos.y) / M_PI;
                    return clamp(abs(mod(theta + vec3(0.0, 4.0, 2.0), 6.0) - 3.0) - 1.0, 0.0, 1.0);
                }
                
                void main()
                {
                    vec2 mouse = vec2(2., -2.) * (i_mouse.xy - 0.5 * i_resolution.xy) / i_resolution.y;
                    vec2 uv = vec2(2., -2.) * (qt_TexCoord0 - 0.5);
                    
                    float l = length(uv);
                    float m = length(mouse);
                    
                    gl_FragColor = i_background;
                    
                    if (l >= 0.75 && l <= 1.0) {
                        l = 1.0 - abs((l - 0.875) * 8.0);
                        l = clamp(l * i_resolution.y * 0.0625, 0.0, 1.0);
                        
                        gl_FragColor = vec4(l * getHueColor(uv), l);
                    } else if (l < 0.75) {
                        if (abs(i_mouse2.x / i_resolution.x - qt_TexCoord0.x) == 0.01 && abs(i_mouse2.y / i_resolution.y - qt_TexCoord0.y) == 0.01) {
                            gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
                        } else {
                            vec3 pickedHueColor;
                            
                            if (m < 0.75 || m > 1.0) {
                                mouse = vec2(0.0, -1.0);
                                pickedHueColor = vec3(1.0, 0.0, 0.0);
                            } else {
                                pickedHueColor = getHueColor(mouse);
                            }
                            
                            uv = uv / 0.75;
                            mouse = normalize(mouse);
                            
                            float sat = 1.5 - (dot(uv, mouse) + 0.5); // [0.0,1.5]
                            
                            if (sat < 1.5) {
                                float h = sat / sqrt(3.0);
                                vec2 om = vec2(cross(vec3(mouse, 0.0), vec3(0.0, 0.0, 1.0)));
                                float lum = dot(uv, om);
                                
                                if (abs(lum) <= h) {
                                    l = clamp((h - abs(lum)) * i_resolution.y * 0.5, 0.0, 1.0) * clamp((1.5 - sat) / 1.5 * i_resolution.y * 0.5, 0.0, 1.0); // Fake antialiasing
                                    gl_FragColor = vec4(l * mix(pickedHueColor, vec3(0.5 * (lum + h) / h), sat / 1.5), l);
                                }
                            }
                        }
                    }
                }";

            
            /*fragmentShader: "#ifdef GL_ES
precision mediump float;
#endif

#define TWO_PI 6.28318530718
const float M_PI = 3.14159265359;

uniform vec2 u_resolution;
uniform vec4 u_background;
uniform float t_lightness;
uniform float t_hue;
uniform float t_saturation;
varying highp vec2 qt_TexCoord0;
uniform lowp float qt_Opacity;

vec3 hsl2rgb(in vec3 c)
{
    vec3 rgb = clamp(abs(mod(c.x * 6.0 + vec3(0.0, 4.0, 2.0), 6.0) - 3.0) -1.0, 0.0, 1.0);
    return c.z + c.y * (rgb - 0.5) * (1.0 -abs(2.0 * c.z - 1.0));
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
        gl_FragColor = u_background;
    }
}";*/
           /* MouseArea {
                anchors.fill: parent
                onClicked: {
                    colorWheel.grabToImage(function(result) {
                        Kontrast.textColor = Kontrast.pixelAt(result.image, mouseX, mouseY);
                        const mouse1X = 2 * (mouseX - 0.5 * colorWheel.width) / colorWheel.height;
                        const mouse1Y = -2 * (mouseY - 0.5 * colorWheel.width) / colorWheel.height;
                        
                        const mouseLenght = Math.sqrt(Math.pow(mouse1X, 2) + Math.pow(mouse1Y, 2));
                        if (mouseLenght > 0.75 && mouseLenght < 1.0) {
                            colorWheel.i_mouse.x = mouseX;
                            colorWheel.i_mouse.y = mouseY;
                        } else {
                            colorWheel.i_mouse2.x = mouseX;
                            colorWheel.i_mouse2.y = mouseY;
                        }
                    });
                }
            }
        }*/
    }
}
