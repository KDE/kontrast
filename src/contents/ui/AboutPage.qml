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

Kirigami.AboutPage {
    aboutData: Kontrast.about
}
