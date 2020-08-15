/*
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 * 
 * SPDX-LicenseRef: GPL-3.0-or-later
 */
#include <QApplication>
#include <QCommandLineParser>
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
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("kontrast");
    
    KAboutData aboutData(QStringLiteral("kontrast"), i18nc("@title", "Kontrast"), QStringLiteral("1.0"),
                         i18nc("@title", "A contrast checker application"),
                         KAboutLicense::GPL_V3);
    
    aboutData.addAuthor(i18nc("@info:credit", "Carl Schwan"), i18nc("@info:credit", "Maintainer and creator"), QStringLiteral("carl@carlschwan.eu"), QStringLiteral("https://carlschwan.eu"));
    aboutData.addCredit(i18nc("@info:credit", "Wikipedia"), i18nc("@info:credit", "Text on the main page CC-BY-SA-4.0"));
    aboutData.addAuthor(i18nc("@info:credit", "Carson Black"), i18nc("@info:credit", "SQLite backend for favorite colors"));

    KAboutData::setApplicationData(aboutData);
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("org.kde.kontrast")));

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    Kontrast kontrast(aboutData);
    kontrast.random();

    QQmlApplicationEngine engine;
    
    qmlRegisterSingletonInstance("org.kde.kontrast.private", 1, 0, "Kontrast", &kontrast);
    qmlRegisterSingletonInstance("org.kde.kontrast.private", 1, 0, "ColorStore", new SavedColorModel(qApp));

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
