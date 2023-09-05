#ifndef THREADCOLORCOLLECTION_H
#define THREADCOLORCOLLECTION_H

#include <QAbstractListModel>
#include "threadcolormodel.h"
#include <QVector>

class ThreadColorCollection : public QAbstractListModel
{
Q_OBJECT
public:
    const int MAX_THREAD_COUNT = 5;
    enum Role {
        ThreadRole = Qt::UserRole + 1,
    };
    Q_ENUM(Role)

    explicit ThreadColorCollection(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
public:
    void addThread(ThreadColorModel* thread);
    void removeThread(int index);
private:
    QVector<ThreadColorModel*> m_threads;
};

Q_DECLARE_METATYPE(ThreadColorCollection*)
#endif // THREADCOLORCOLLECTION_H
