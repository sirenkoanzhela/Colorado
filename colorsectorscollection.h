#ifndef COLORSECTORSCOLLECTION_H
#define COLORSECTORSCOLLECTION_H
#include <QAbstractListModel>
#include <QVector>
#include <QColor>

class ColorSectorsCollection : public QAbstractItemModel
{
    Q_OBJECT
public:
    const int MAX_THREAD_COUNT = 5;
    const int MAX_SECTOR_COUNT = 5;
    enum Role {
        ThreadRole = Qt::UserRole + 1,
        ColorRole = Qt::UserRole + 2,
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

    Q_INVOKABLE QModelIndex createIndex(int row, int column) const {
        return QAbstractItemModel::createIndex(row, column);
    }

    explicit ColorSectorsCollection(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;  //  return count of threads
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex index(int row, int column,  const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    int getThreadCount(const QModelIndex &parent = QModelIndex()) const;  //  return count of sectors in specific thread by index
public:
    void addThread();
    void removeThread(const QModelIndex &index);

signals:
    void sectorsCountChanged();

public:
    Q_INVOKABLE void addSector(const QModelIndex &index);
    Q_INVOKABLE void removeSector(const QModelIndex &index);
    Q_INVOKABLE void removeSector(const QModelIndex &threadIndex, const QModelIndex &highlightedSectorIndex);
    Q_INVOKABLE void changeSectorColor(const QModelIndex &threadIndex,const QModelIndex &colorIndex, QColor color);
    Q_INVOKABLE bool canRemoveSector(const QModelIndex &index) const;
private:
    QVector<QVector<QColor>> m_collection;

    int m_highlighted_color_index = -1;
};

#endif // COLORSECTORSCOLLECTION_H
