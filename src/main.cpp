#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QUrl>
#include <QIcon>
#include <KLocalizedContext>
#include <KAboutData>
#include <KLocalizedString>
#include <kontrast.h>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    
    KAboutData aboutData("kontrast", i18n("Kontrast"), "1.0",
                         i18n("A contrast checked application"),
                         KAboutLicense::GPL);
    
    KAboutData::setApplicationData(aboutData);
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("kontrast")));
    
    QScopedPointer<Kontrast> kontrast(new Kontrast(aboutData));
    kontrast.get()->random();

    QQmlApplicationEngine engine;
    
    qmlRegisterSingletonInstance("org.kde.kontrast.private", 1, 0, "Kontrast", kontrast.get());

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
