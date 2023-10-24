#include "datahandler.h"
#include <QDir>
#include <QDebug>

DataHandler::DataHandler(QObject *parent)
    : QObject(parent)
{

}

void DataHandler::saveData(const QVector<QVector<QColor>> &collection)
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
        else
        {
            qDebug() << "Cannot open file, data won't be saved";
        }
        //else
        //clang
        //make files
        // header with path
}

QVector<QVector<QColor>> DataHandler::loadData()
{

        QFile file(QDir::currentPath() + "/saved.dat");
        if(isDataExists() && file.open(QIODevice::ReadOnly))
        {
            //add check size
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
