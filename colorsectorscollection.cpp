#include "colorsectorscollection.h"
#include <iostream>
#include <QDebug>

ColorSectorsCollection::ColorSectorsCollection(QObject *parent)
    : QAbstractListModel(parent)
{
    qRegisterMetaType<ColorSectorsCollection*>("ColorSectorsCollection*");



    if( m_data_handler.isDataExists())
    {
        m_collection = m_data_handler.loadData();
    }
    else
    {
        m_collection.reserve(MAX_THREAD_COUNT);
        for(int i = 0; i < m_collection.capacity(); ++i)
        {
            QVector<QColor> colorThread;
            colorThread.reserve(MAX_SECTOR_COUNT - i);
            for(int j = 0; j<colorThread.capacity(); ++j)
            {
                QColor col;
                col = Qt::white;
                colorThread.append(col);

            }
            m_collection.append(colorThread);
        }
    }

    // initial create 5 threads. Todo: make colorThreads count dynamic
    // with posibility to add or remove colorThread
}

int ColorSectorsCollection::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_collection.count();
}

QModelIndex ColorSectorsCollection::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }
    return createIndex(row, column);

    assert(false);
    return QModelIndex();
}

int ColorSectorsCollection::getThreadCount(const QModelIndex &parent) const
{
    if (parent.row() < 0 || parent.row() >= m_collection.count())
    {
        return 0;
    }
    return m_collection[parent.row()].count();
}

QVariant ColorSectorsCollection::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_collection.size())
    {
        return QVariant();
    }

    const QVector<QColor> &thread = m_collection.at(index.row());

    if (thread.isEmpty())
    {
        return QVariant();
    }

    switch (role)
    {
        case ThreadRole:
        {
            return QVariant::fromValue(thread);
        }
        default:
        {
            return QVariant();
        }
    }
}

QHash<int, QByteArray> ColorSectorsCollection::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ThreadRole] = "thread";
    roles[ColorRole] = "color";

    return roles;
}

void ColorSectorsCollection::addThread()
{
    if(m_collection.count() < MAX_THREAD_COUNT)
    {
        beginInsertRows(QModelIndex(), m_collection.count(), m_collection.count());
        QVector<QColor> colorThread;
        m_collection.append(colorThread);
        endInsertRows();
    }
}

void ColorSectorsCollection::removeThread(const QModelIndex &index)
{
    if (index.row() < 0 || index.row() >= m_collection.count())
        return;

    int row = index.row();

    beginRemoveRows(QModelIndex(), row, row);
    m_collection.removeAt(row);
    endRemoveRows();
}


void ColorSectorsCollection::addSector(const int &index)
{
    if( index < 0 || index >= m_collection.size() || m_collection.at(index).isEmpty())
    {
        return;
    }

    if(m_collection.at(index).size() < MAX_SECTOR_COUNT)
    {
        beginResetModel();
        m_collection[index].append(QColor(Qt::white));
        endResetModel();
        emit sectorsCountChanged();
        m_data_handler.saveData(m_collection);
    }

}

void ColorSectorsCollection::removeSector(const int &index)
{
    if( index < 0 || index >= m_collection.size() || m_collection.at(index).isEmpty())
    {
        return;
    }

    if(m_collection.at(index).size() > 1)
    {
        beginResetModel();
        m_collection[index].removeLast();
        endResetModel();
        emit sectorsCountChanged();
        m_data_handler.saveData(m_collection);
    }
}

void ColorSectorsCollection::removeSector(const int &index,  const int &highlightedSectorIndex)
{
    if( index < 0 || index >= m_collection.size() || m_collection.at(index).isEmpty())
    {
        return;
    }
    if( highlightedSectorIndex >= m_collection.at(index).size() || highlightedSectorIndex < 0)
    {
        return;
    }

    if(m_collection.isEmpty() || m_collection.at(index).isEmpty() )
    {
        return;
    }

    if(m_collection.at(index).size() > 1)
    {
        beginResetModel();
        m_collection[index].remove(highlightedSectorIndex);
        endResetModel();
        emit sectorsCountChanged();
    }
}

void ColorSectorsCollection::changeSectorColor(const QModelIndex &threadIndex,const QModelIndex &colorIndex, QColor color)
{
    if (!threadIndex.isValid() || !colorIndex.isValid())
        return;
    m_collection[threadIndex.row()][colorIndex.row()] = color;
    emit dataChanged(index(threadIndex.row(), colorIndex.column()), index(threadIndex.row(), colorIndex.column()), {ColorRole});
}

bool ColorSectorsCollection::isRemoveSectorEnable(const int &index) const
{
    if(index < 0 || index >= m_collection.size())
    {
        return false;
    }
    if(m_collection.at(index).size() > 1)
    {
        return true;
    }
    return false;
}

bool ColorSectorsCollection::isRemoveSectorEnable(const int &index, const int &highlightedIndex) const
{
    if( highlightedIndex < 0)
    {
        return false;
    }
    if(index < 0 || index >= m_collection.size())
    {
        return false;
    }
    if(m_collection.at(index).size() > 1)
    {
        return true;
    }
    return false;
}

bool ColorSectorsCollection::isAddSectorEnable(const int &index) const
{
    if(index < 0 || index >= m_collection.size())
    {
        return false;
    }
    if(m_collection.at(index).size() < MAX_SECTOR_COUNT)
    {
        return true;
    }
    return false;

}

int ColorSectorsCollection::getThreadSize(const int &index) const
{
    if( index < 0 || index >= m_collection.size() || m_collection.at(index).isEmpty())
    {
        return 0;
    }
    return m_collection.at(index).size();
}
