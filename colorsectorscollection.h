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
    const int MAX_SECTOR_COUNT = 6;
    enum Role {
        ThreadRole = Qt::UserRole + 1,
        ColorRole = Qt::UserRole + 10,
    };
    Q_ENUM(Role)

    enum InitialColor {
        red = Qt::UserRole +1,
        black,
        yellow,
        white,
        grey,
    };
    Q_ENUM(InitialColor)


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
    void sectorsCountChanged();

public:
    Q_INVOKABLE void addSector(const int &index);
    Q_INVOKABLE void removeSector(const int &index);
    Q_INVOKABLE void removeSector(const int &threadIndex, const int &highlightedSectorIndex);
    Q_INVOKABLE void changeSectorColor(const QModelIndex &threadIndex,const QModelIndex &colorIndex, QColor color);
    Q_INVOKABLE bool isRemoveSectorEnable(const int &index) const;
    Q_INVOKABLE bool isAddSectorEnable(const int &index) const;
    Q_INVOKABLE int getThreadSize(const int &index) const;

    Q_INVOKABLE QModelIndex createIndex(int row, int column) const {
        return QAbstractListModel::createIndex(row, column);
    }
    Q_INVOKABLE QColor getColorForIndices(int outerIndex, int innerIndex) const {
        if (outerIndex < 0  || outerIndex >= m_collection.size() || innerIndex < 0 || innerIndex >= m_collection.at(outerIndex).size())
        {
            return QColor();
        }

        const QVector<QColor> &thread = m_collection.at(outerIndex);
        return thread.at(innerIndex);
    }

private:
    QVector<QVector<QColor>> m_collection;

    int m_highlighted_color_index = -1;
    DataHandler m_data_handler;
};

#endif // COLORSECTORSCOLLECTION_H
