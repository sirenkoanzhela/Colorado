#include "colorsectorscollection.h"
#include <iostream>

ColorSectorsCollection::ColorSectorsCollection(QObject *parent)
    : QAbstractItemModel(parent)
{
    qRegisterMetaType<ColorSectorsCollection*>("ColorSectorsCollection*");


    // initial create 5 threads. Todo: make colorThreads count dynamic
    // with posibility to add or remove colorThread

    std::cout << "ThreadColorCollection constructor" << std::endl;

    //------------------------------------------------------
    // this part as added to simulate the filled 5 threads
    // to debug collection model
    // in future, there will be possibility to load
    // data from file or DB

    // todo: add data loader

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

    for(int i = 0; i< m_collection.size(); ++i)
    {
        std::cout << i << " thread. Its size = " << m_collection.at(i).size() << std::endl;
        for( int j = 0; j < m_collection.at(i).size(); ++j)
        {
            std::cout << "[i][j] = " <<m_collection.at(i).front().name().toStdString() << " ";
        }
    }
    //------------------------------------------------------
}

int ColorSectorsCollection::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_collection.count();
}

int ColorSectorsCollection::columnCount(const QModelIndex &parent) const
{
    //return m_collection[parent.row()].count(); //add check

    return m_collection.at(parent.row()).count();


    // from Qt Documentation:
    // When implementing a table based model, columnCount() should return 0 when the parent is valid.
    if (!parent.isValid())
    {
        int maxColumns = 0;
        for (const auto& subvector : m_collection)
        {
            if (subvector.count() > maxColumns)
                maxColumns = subvector.count();
        }
        return maxColumns;
    }
    return 0;
}

QModelIndex ColorSectorsCollection::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid()) {  // Если родителя нет, то это тред.
        return createIndex(row, column);
    }

    assert(false);
    return QModelIndex();  // Этот код не должен быть достигнут, но для безопасности мы возвращаем невалидный индекс.
}

QModelIndex ColorSectorsCollection::parent(const QModelIndex &) const
{
    //Q_UNUSED(index);
    return QModelIndex();  // Всегда возвращаем невалидный индекс, так как у нас нет иерархии.
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
    // Проверка допустимости индекса
    if (!index.isValid() || index.row() < 0 || index.row() >= m_collection.size())
        return QVariant();

    // Получение соответствующего потока
    const QVector<QColor> &thread = m_collection.at(index.row()); //at - throw exeption

    // Проверка допустимости столбца (он соответствует индексу цвета в потоке)
    if (index.column() < 0 || index.column() >= thread.size())
        return QVariant();

    // В зависимости от роли возвращаем значение
    switch (role) {
        case ThreadRole:
            return QVariant::fromValue(thread);  // Возвращает целиком поток цветов

        case ColorRole:
            return QVariant::fromValue(thread.at(index.column()));  // Возвращает конкретный цвет из потока

        default:
            return QVariant();  // Невалидное значение для неизвестной роли
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
        m_collection.append(colorThread); //emplace why better?
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


void ColorSectorsCollection::addSector(const QModelIndex &index)
{
    if( !index.isValid() )
    {
        return;
    }

    if( m_collection[index.row()].count() < MAX_SECTOR_COUNT ){
        beginInsertColumns(QModelIndex(), rowCount(), rowCount());
        m_collection[index.row()].append(QColor(Qt::white));
        endInsertColumns();
        emit sectorsCountChanged();
    }
}

void ColorSectorsCollection::removeSector(const QModelIndex &index)
{
    if(!index.isValid())
    {
        return;
    }
    if(m_collection.isEmpty() || m_collection[index.row()].isEmpty() )
    {
        return;
    }
    int lastSectorIndex = m_collection[index.row()].count() - 1;

    beginRemoveColumns(QModelIndex(), lastSectorIndex, lastSectorIndex);
    m_collection[index.row()].removeLast();
    endRemoveColumns();

    emit sectorsCountChanged();

    std::cout << "Removed sector" << std::endl;
    std::cout << "Now sectors count is : " <<m_collection[index.row()].size() << std::endl;
}

void ColorSectorsCollection::removeSector(const QModelIndex &index,  const QModelIndex &highlightedSectorIndex)
{
    if (!index.isValid() || !highlightedSectorIndex.isValid())
    {
        return;
    }

    if(m_collection.isEmpty() || m_collection[index.row()].isEmpty() )
    {
        return;
    }

    int row = index.row();

    beginRemoveColumns(QModelIndex(), row, row);
    m_collection[index.row()].removeAt(row);
    endRemoveColumns();

    emit sectorsCountChanged();

    std::cout << "Removed sector with index: " << index.row() << std::endl;
    std::cout << "Now sectors count is : " <<m_collection[index.row()].size() << std::endl;
}

void ColorSectorsCollection::changeSectorColor(const QModelIndex &threadIndex,const QModelIndex &colorIndex, QColor color)
{
    if (!threadIndex.isValid() || !colorIndex.isValid())
        return;
    m_collection[threadIndex.row()][colorIndex.row()] = color;
    emit dataChanged(index(threadIndex.row(), colorIndex.column()), index(threadIndex.row(), colorIndex.column()), {ColorRole});
}

bool ColorSectorsCollection::canRemoveSector(const QModelIndex &index) const
{
    if (!index.isValid())
        return false;
    if (m_collection.isEmpty() || m_collection.at(index.row()).isEmpty())
        return false;
    return m_collection.at(index.row()).count() > 1;
}
