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
#include "kontrast.h"
#ifndef Q_OS_ANDROID
#include <KCrash>
#endif
#include <QCommandLineParser>
#include <QDir>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QUrl>

const QString DRIVER(QStringLiteral("QSQLITE"));

Q_DECL_EXPORT int main(int argc, char *argv[])
{
#ifndef Q_OS_ANDROID
    QApplication app(argc, argv);
#else
    QGuiApplication app(argc, argv);
#endif
    KLocalizedString::setApplicationDomain(QByteArrayLiteral("kontrast"));

    KAboutData aboutData(QStringLiteral("kontrast"),
                         i18nc("@title", "Kontrast"),
                         QStringLiteral(KONTRAST_VERSION_STRING),
                         i18nc("@title", "A contrast checker application"),
                         KAboutLicense::GPL_V3);

    aboutData.addAuthor(i18nc("@info:credit", "Carl Schwan"),
                        i18nc("@info:credit", "Maintainer and creator"),
                        QStringLiteral("carl@carlschwan.eu"),
                        QStringLiteral("https://carlschwan.eu"),
                        QUrl{QStringLiteral("https://carlschwan.eu/avatar.png")});
    aboutData.addCredit(i18nc("@info:credit", "Wikipedia"), i18nc("@info:credit", "Text on the main page CC-BY-SA-4.0"));
    aboutData.addAuthor(i18nc("@info:credit", "Carson Black"), i18nc("@info:credit", "SQLite backend for favorite colors"));
    aboutData.setTranslator(i18nc("NAME OF TRANSLATORS", "Your names"), i18nc("EMAIL OF TRANSLATORS", "Your emails"));

    KAboutData::setApplicationData(aboutData);
#ifndef Q_OS_ANDROID
    KCrash::initialize();
#endif
    QGuiApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("org.kde.kontrast")));

    Q_ASSERT(QSqlDatabase::isDriverAvailable(DRIVER));
    bool success = QDir().mkpath(QDir::cleanPath(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)));
    Q_ASSERT(success);

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.loadFromModule("org.kde.kontrast", "Main");

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
