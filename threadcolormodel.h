#ifndef THREADCOLORMODEL_H
#define THREADCOLORMODEL_H

#include <QAbstractListModel>
#include <QColor>
#include <QVector>

class ThreadColorModel : public QAbstractListModel
{
    Q_OBJECT
public:
    const int MAX_SECTOR_COUNT = 5;
    enum Role {
        ColorRole = Qt::UserRole + 1,
    };
    Q_ENUM(Role)

    explicit ThreadColorModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   // int rowCount(const QModelIndex &parent = QModelIndex(),const QModelIndex &parent2 = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;
signals:
    void sectorsCountChanged();
public:
    Q_INVOKABLE void addSector();
    Q_INVOKABLE void removeSector();
    Q_INVOKABLE void removeSector(const QModelIndex &index);
    Q_INVOKABLE void changeSectorColor(const QModelIndex &index, QColor color);
private:
    QVector<QColor> m_colorSectors;
};

Q_DECLARE_METATYPE(ThreadColorModel*)

#endif // THREADCOLORMODEL_H
