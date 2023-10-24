#include "mainwindow.h"
#include "palettemodel.h"
#include "colorsectorscollection.h"

#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    PaletteModel paletteModel;

    ColorSectorsCollection colorSectorsCollection;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/MainPage.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("colorSectorsCollection", &colorSectorsCollection);
    engine.rootContext()->setContextProperty("paletteModel", &paletteModel);
    engine.load(url);

    return app.exec();
}
