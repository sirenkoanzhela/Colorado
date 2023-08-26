#include "mainwindow.h"
#include "userpage.h"
#include "colorcontainer.h"

#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    UserPage userpage;
    ColorContainer colorContainer;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/MainPage.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("userpage", &userpage);
    engine.rootContext()->setContextProperty("container", &colorContainer);
    engine.load(url);
    return app.exec();
}
