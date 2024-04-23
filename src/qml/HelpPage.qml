/**
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.1
import org.kde.kirigami 2.6 as Kirigami
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.15 as QQC2

Kirigami.ScrollablePage {
    title: i18nc("@title:menu", "Help")
    ColumnLayout {
        width: parent.width
        Kirigami.Heading {
            Layout.fillWidth: true
            level: 1
            text: i18nc("@title:heading", "Contrast")
        }
        QQC2.Label {
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            text: i18n("Contrast is the difference in color between two objects that allows them to be distinguished. In visual perception of the real world, contrast is determined by the difference in the color and brightness of the object and other objects within the same field of view.")
        }
        QQC2.Label {
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            text: i18n("A contrast value of 21 indicates a perfect contrast (usually black on white), and a value of 0 indicate that the two colors are the same.")
        }
        QQC2.Label {
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            text: i18n("For normal text, the contrast ratio should be at least of 4.5 to conform to the WCAG AA standard and a contrast ratio of 7 or more is required to conform with the WCAG AAA standard.")
        }
        QQC2.Label {
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            text: i18n("For large text, the contrast ratio should be at least of 3 to conform to the WCAG AA standard and a contrast ratio of 4.5 or more is required to conform with the WCAG AAA standard.")
        }
    }
}

