#ifndef COLORSECTORSCOLLECTION_H
#define COLORSECTORSCOLLECTION_H
#include <QAbstractListModel>
#include <QVector>
#include <QColor>
#include "datahandler.h"

class ColorSectorsCollection : public QAbstractListModel
{
    Q_OBJECT
public:
    const int MAX_THREAD_COUNT = 5;
    const int MAX_SECTORS_IN_THREAD_COUNT = 6;
    enum Role {
        ThreadRole = Qt::UserRole + 1,
        ColorRole = Qt::UserRole + 10,
    };
    Q_ENUM(Role)

    explicit ColorSectorsCollection(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;  //  return count of threads
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    int getThreadCount(const QModelIndex &parent = QModelIndex()) const;  //  return count of sectors in specific thread by index
public:
    void addThread();
    void removeThread(const QModelIndex &index);

signals:
    void sectorsCountChanged(QVector<QVector<QColor>> m_collection);
    void sectorColorChanged(QVector<QVector<QColor>> m_collection);

public:
    //count functionality
    Q_INVOKABLE void addSector(const int &index);
    Q_INVOKABLE void removeSector(const int &index);
    Q_INVOKABLE void removeSector(const int &threadIndex, const int &highlightedSectorIndex);
    Q_INVOKABLE bool isRemoveSectorEnable(const int &index) const;
    Q_INVOKABLE bool isRemoveSectorEnable(const int &index, const int &highlightedIndex) const;
    Q_INVOKABLE bool isAddSectorEnable(const int &index) const;
    Q_INVOKABLE int getThreadSize(const int &index) const;
    Q_INVOKABLE QModelIndex createIndex(int row, int column) const;

    //color functionality
    Q_INVOKABLE bool tryChangeSectorColor(const int &threadIndex,const int &colorIndex, QString color);
    Q_INVOKABLE QColor getColorForIndices(int outerIndex, int innerIndex) const;

private:
    void initializeCollection();
    bool colorValidation(const QString &color);
    void formatColor(QString& color);

private:
    QVector<QVector<QColor>> m_collection;
    DataHandler m_data_handler;
};

#endif // COLORSECTORSCOLLECTION_H
