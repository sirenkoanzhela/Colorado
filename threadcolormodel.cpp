#include "threadcolormodel.h"
#include <iostream>


ThreadColorModel::ThreadColorModel(QObject *parent)
    : QAbstractListModel(parent)
{
    qRegisterMetaType<ThreadColorModel*>("ThreadColorModel*");

    //initiation with white color, as colorThread cannot be empty
    m_colorSectors.append(QColor(Qt::white));
    std::cout << "ThreadColorModel constructor" << std::endl;
}

int ThreadColorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_colorSectors.size();
}

QVariant ThreadColorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() < 0 || index.row() >= m_colorSectors.count())
        return QVariant();
    if (role == ColorRole)
    {
        QVariant colorVariant;
        colorVariant.setValue(m_colorSectors.at(index.row()));
        return colorVariant;
    }
    return QVariant();
}

bool ThreadColorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (role == ColorRole)
    {
        changeSectorColor(index, value.value<QColor>());
        emit dataChanged(index, index, { role });
        return true;
    }
    return false;
}

QHash<int, QByteArray> ThreadColorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ColorRole] = "color";
    return roles;
}

void ThreadColorModel::addSector()
{
    if(rowCount() < MAX_SECTOR_COUNT){
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_colorSectors.append(QColor(Qt::white));
        endInsertRows();
        emit sectorsCountChanged();
    }
}

void ThreadColorModel::removeSector()
{
    if(m_colorSectors.isEmpty())
    {
        return;
    }
    int lastIndex = m_colorSectors.count() - 1;

    beginRemoveRows(QModelIndex(), lastIndex, lastIndex);
    m_colorSectors.removeLast();
    endRemoveRows();
    emit sectorsCountChanged();
    std::cout << "Removed sector" << std::endl;
    std::cout << "Now sectors count is : " << m_colorSectors.size() << std::endl;
}

void ThreadColorModel::removeSector(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    if(m_colorSectors.isEmpty())
    {
        return;
    }

    int row = index.row();

    beginRemoveRows(QModelIndex(), row, row);
    m_colorSectors.removeAt(row);
    endRemoveRows();
    emit sectorsCountChanged();
    std::cout << "Removed sector with index: " << index.row() << std::endl;
    std::cout << "Now sectors count is : " << m_colorSectors.size() << std::endl;
}

void ThreadColorModel::changeSectorColor(const QModelIndex &index, QColor color)
{
    if (!index.isValid())
        return;
    m_colorSectors[index.row()] = color;
}
