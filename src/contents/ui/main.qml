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


Kirigami.ApplicationWindow {
    id: root

    
    Kirigami.PagePool {
        id: mainPagePool
    }

    globalDrawer: Kirigami.GlobalDrawer {
        title: i18n("kontrast")
        titleIcon: "applications-graphics"
        isMenu: true
        actions: [
            Kirigami.PagePoolAction {
                text: i18n("Contrast Checker")
                icon.name: "go-home"
                pagePool: mainPagePool
                page: "MainPage.qml"
            },
            Kirigami.PagePoolAction {
                text: i18n("Favorite Colors")
                icon.name: "favorite"
                pagePool: mainPagePool
                page: "FavoritePage.qml"
            },
            Kirigami.PagePoolAction {
                text: i18n("Help")
                icon.name: "help-contents"
                pagePool: mainPagePool
                page: "HelpPage.qml"
            },
            Kirigami.PagePoolAction {
                text: i18n("About")
                icon.name: "help-about-symbolic"
                pagePool: mainPagePool
                page: "AboutPage.qml"
            }
        ]
    }

    contextDrawer: Kirigami.ContextDrawer {
        id: contextDrawer
    }

    pageStack.initialPage: mainPagePool.loadPage("MainPage.qml")
}
