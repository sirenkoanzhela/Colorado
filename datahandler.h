#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QFile>
#include <QDataStream>
#include <QVector>
#include <QColor>

class DataHandler
{
public:
    DataHandler();

    void saveData(QVector<QVector<QColor>> collection);
    QVector<QVector<QColor>> loadData();
    bool isDataExists();
};

#endif // DATAHANDLER_H
