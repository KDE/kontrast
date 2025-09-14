/**
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

pragma ComponentBehavior: Bound

import QtQuick
import org.kde.kirigami as Kirigami
import QtQuick.Window
import org.kde.config as KConfig

Kirigami.ApplicationWindow {
    id: root

    KConfig.WindowStateSaver {
        configGroupName: "MainWindow"
    }

    Kirigami.PagePool {
        id: mainPagePool
    }

    globalDrawer: Kirigami.GlobalDrawer {
        title: i18n("Kontrast")
        titleIcon: "applications-graphics"
        isMenu: true
        actions: [
            Kirigami.PagePoolAction {
                id: contrastChecker
                text: i18nc("@title:menu", "Contrast Checker")
                icon.name: "go-home"
                pagePool: mainPagePool
                page: "MainPage.qml"
                initialProperties: {
                    return { contrastChecker };
                }
            },
            Kirigami.PagePoolAction {
                text: i18nc("@title:menu", "Favorite Colors")
                icon.name: "favorite"
                pagePool: mainPagePool
                page: "FavoritePage.qml"
            },
            Kirigami.PagePoolAction {
                text: i18nc("@title:menu", "Help")
                icon.name: "help-contents"
                pagePool: mainPagePool
                page: "HelpPage.qml"
            },
            Kirigami.PagePoolAction {
                text: i18nc("@title:menu", "About")
                icon.name: "help-about-symbolic"
                pagePool: mainPagePool
                page: Qt.createComponent("org.kde.kirigamiaddons.formcard", "AboutPage").url
            }
        ]
    }

    contextDrawer: Kirigami.ContextDrawer {
        id: contextDrawer
    }

    pageStack.initialPage: mainPagePool.loadPage("MainPage.qml")
}
