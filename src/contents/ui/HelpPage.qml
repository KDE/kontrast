/**
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-LicenseRef: GPL-3.0-or-later
 */

import QtQuick 2.1
import org.kde.kirigami 2.6 as Kirigami
import QtQuick.Layouts 1.14

Kirigami.ScrollablePage {
    title: i18n("Help")
    ColumnLayout {
        width: parent.width
        Kirigami.Heading {
            Layout.fillWidth: true
            level: 1
            text: i18n("Contrast")
        } 
        Text {
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            text: i18n("Contrast is the difference in color between two objects that allows them to be distinguished. In visual perception of the real world, contrast is determined by the difference in the color and brightness of the object and other objects within the same field of view.")
        }
        Text {
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            text: i18n("A contrast value of 21 indicates a perfect contrast (ussually black on white), and a value of 0 indicate that the two colors are the same.")
        }
        Text {
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            text: i18n("For normal text, the contrast ratio should be at least of 4.5 to conform to the WSGA AA standard and a contrast ratio of 7 or more is required to conform with the WSGA AAA standard.")
        }
        Text {
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            text: i18n("For large text, the contrast ratio should be at least of 3 to conform to the WSGA AA standard and a contrast ratio of 4.5 or more is required to conform with the WSGA AAA standard.")
        }
    }
}
