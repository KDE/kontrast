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
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setApplicationName("Kontrast");
    
    KAboutData aboutData("kontrast", i18n("Kontrast"), "1.0",
                         i18n("A contrast checker application"),
                         KAboutLicense::GPL_V3);
    
    aboutData.addAuthor(i18n("Carl Schwan"), i18n("Maintainer and creator"), "carl@carlschwan.eu", "https://carlschwan.eu");
    aboutData.addCredit(i18n("Wikipedia"), i18n("Text on the main page CC-BY-SA-4.0"));
    aboutData.addAuthor(i18n("Carson Black"), i18n("SQLite backend for favorite colors"));

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
