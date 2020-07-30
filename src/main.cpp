/*
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-LicenseRef: GPL-3.0-or-later
 */
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QUrl>
#include <QIcon>
#include <KLocalizedContext>
#include <KAboutData>
#include <KLocalizedString>
#include <kontrast.h>
#include "savedcolormodel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    KLocalizedString::setApplicationDomain("kontrast");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setApplicationName("Kontrast");
    
    KAboutData aboutData("kontrast", xi18nc("@title", "Kontrast"), "1.0",
                         xi18nc("@title", "A contrast checker application"),
                         KAboutLicense::GPL_V3);
    
    aboutData.addAuthor(xi18nc("@info:credit", "Carl Schwan"), xi18nc("@info:credit", "Maintainer and creator"), "carl@carlschwan.eu", "https://carlschwan.eu");
    aboutData.addCredit(xi18nc("@info:credit", "Wikipedia"), xi18nc("@info:credit", "Text on the main page CC-BY-SA-4.0"));
    aboutData.addAuthor(xi18nc("@info:credit", "Carson Black"), xi18nc("@info:credit", "SQLite backend for favorite colors"));

    KAboutData::setApplicationData(aboutData);
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("kontrast")));
    
    QScopedPointer<Kontrast> kontrast(new Kontrast(aboutData));
    kontrast.get()->random();

    QQmlApplicationEngine engine;
    
    qmlRegisterSingletonInstance("org.kde.kontrast.private", 1, 0, "Kontrast", kontrast.get());
    qmlRegisterSingletonInstance("org.kde.kontrast.private", 1, 0, "ColorStore", new SavedColorModel(qApp));

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
