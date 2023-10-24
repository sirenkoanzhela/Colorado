#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QObject>
#include <QFile>
#include <QDataStream>
#include <QVector>
#include <QColor>

//todo: make it template and use also in modelPalette
class DataHandler : public QObject
{
    Q_OBJECT
public:
    DataHandler(QObject *parent = nullptr);

    QVector<QVector<QColor>> loadData();
    bool isDataExists();
public slots:
    void saveData(const QVector<QVector<QColor>> &collection);
};

#endif // DATAHANDLER_H
