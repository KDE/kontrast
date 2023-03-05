/*
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include "config-kontrast.h"
#include "savedcolormodel.h"
#include <KAboutData>
#include <KLocalizedContext>
#include <KLocalizedString>
#ifndef Q_OS_ANDROID
#include <QApplication>
#else
#include <QGuiApplication>
#endif
#include "clipboard.h"
#include <QCommandLineParser>
#include <QDir>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QUrl>
#include <kontrast.h>

const QString DRIVER(QStringLiteral("QSQLITE"));

Q_DECL_EXPORT int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#ifndef Q_OS_ANDROID
    QApplication app(argc, argv);
#else
    QGuiApplication app(argc, argv);
#endif
    KLocalizedString::setApplicationDomain("kontrast");

    KAboutData aboutData(QStringLiteral("kontrast"),
                         i18nc("@title", "Kontrast"),
                         QStringLiteral(KONTRAST_VERSION_STRING),
                         i18nc("@title", "A contrast checker application"),
                         KAboutLicense::GPL_V3);

    aboutData.addAuthor(i18nc("@info:credit", "Carl Schwan"),
                        i18nc("@info:credit", "Maintainer and creator"),
                        QStringLiteral("carl@carlschwan.eu"),
                        QStringLiteral("https://carlschwan.eu"));
    aboutData.addCredit(i18nc("@info:credit", "Wikipedia"), i18nc("@info:credit", "Text on the main page CC-BY-SA-4.0"));
    aboutData.addAuthor(i18nc("@info:credit", "Carson Black"), i18nc("@info:credit", "SQLite backend for favorite colors"));

    KAboutData::setApplicationData(aboutData);
    QGuiApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("org.kde.kontrast")));

    Q_ASSERT(QSqlDatabase::isDriverAvailable(DRIVER));
    Q_ASSERT(QDir().mkpath(QDir::cleanPath(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation))));
    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    const auto path = QDir::cleanPath(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + QStringLiteral("/") + qApp->applicationName());
    db.setDatabaseName(path);
    if (!db.open()) {
        qCritical() << db.lastError() << "while opening database at" << path;
    }

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    Kontrast kontrast;
    kontrast.random();

    QQmlApplicationEngine engine;

    qmlRegisterSingletonInstance("org.kde.kontrast.private", 1, 0, "Kontrast", &kontrast);
    qmlRegisterSingletonInstance("org.kde.kontrast.private", 1, 0, "ColorStore", new SavedColorModel(qApp));
    qmlRegisterType<Clipboard>("org.kde.kontrast.private", 1, 0, "Clipboard");
    qmlRegisterSingletonType("org.kde.kontrast.private", 1, 0, "About", [](QQmlEngine *engine, QJSEngine *) -> QJSValue {
        return engine->toScriptValue(KAboutData::applicationData());
    });

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
