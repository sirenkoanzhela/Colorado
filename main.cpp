#include "mainwindow.h"
#include "userpage.h"
#include "colorcontainer.h"
//#include "threadcolormodel.h"
//#include "threadcolorcollection.h"
#include "colorsectorscollection.h"

#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    UserPage userpage;
    ColorContainer colorContainer;
    //ThreadColorModel threadColorModel;
    //ThreadColorCollection threadColorCollection;

    ColorSectorsCollection colorSectorsCollection;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/MainPage.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("userpage", &userpage);
    engine.rootContext()->setContextProperty("container", &colorContainer);
    //engine.rootContext()->setContextProperty("threadColor", &threadColorModel);
    //engine.rootContext()->setContextProperty("threadsCollectrion" ,&threadColorCollection);
    engine.rootContext()->setContextProperty("colorSectorsCollection" ,&colorSectorsCollection);
    engine.load(url);
    return app.exec();
}
