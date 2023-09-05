#include "threadcolorcollection.h"
#include "threadcolormodel.h"

#include <iostream>

ThreadColorCollection::ThreadColorCollection(QObject *parent)
    : QAbstractListModel(parent)
{
    qRegisterMetaType<ThreadColorCollection*>("ThreadColorCollection*");

    // initial create 5 threads. Todo: make colorThreads count dynamic
    // with posibility to add or remove colorThread

    std::cout << "ThreadColorCollection constructor" << std::endl;
    m_threads.reserve(MAX_THREAD_COUNT);
    for(int i = 0; i<MAX_THREAD_COUNT; ++i)
    {
        ThreadColorModel* threadColorModel = new ThreadColorModel();
        m_threads.append(threadColorModel);
    }
}

int ThreadColorCollection::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_threads.count();
}

QVariant ThreadColorCollection::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_threads.count())
        return QVariant();

    ThreadColorModel* thread = m_threads[index.row()];

    if (role == ThreadRole)
        return QVariant::fromValue(thread);

    return QVariant();
}

QHash<int, QByteArray> ThreadColorCollection::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ThreadRole] = "thread";
    return roles;
}

void ThreadColorCollection::addThread(ThreadColorModel* thread)
{
    beginInsertRows(QModelIndex(), m_threads.count(), m_threads.count());
    m_threads.append(thread);
    endInsertRows();
}

void ThreadColorCollection::removeThread(int index)
{
    if (index < 0 || index >= m_threads.count())
        return;

    beginRemoveRows(QModelIndex(), index, index);
    m_threads.removeAt(index);
    endRemoveRows();
}
