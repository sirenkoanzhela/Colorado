#include "datahandler.h"
#include <QDir>

DataHandler::DataHandler()
{

}

void DataHandler::saveData(QVector<QVector<QColor>> collection)
{
    QFile file(QDir::currentPath() + "/saved.dat");
        if (file.open(QIODevice::WriteOnly)) {
            QDataStream out(&file);
            out.setVersion(QDataStream::Qt_5_15);

            for (const auto &innerVector : collection) {
                out << innerVector.size();
                for (const QColor &color : innerVector) {
                    out << color;
                }
            }

            file.close();
        }
}

QVector<QVector<QColor>> DataHandler::loadData()
{
    QFile file(QDir::currentPath() + "/saved.dat");
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_5_15);

            QVector<QVector<QColor>> collection;
            collection.clear();

            while (!in.atEnd()) {
                QVector<QColor> innerVector;
                int size;
                in >> size;
                for (int i = 0; i < size; i++) {
                    QColor color;
                    in >> color;
                    innerVector.append(color);
                }
                collection.append(innerVector);
            }

            file.close();
            return collection;
        }
        return QVector<QVector<QColor>>();
}

bool DataHandler::isDataExists()
{
    if (!QFile::exists(QDir::currentPath() + "/saved.dat")) {
        return false;
    }
    return true;
}
