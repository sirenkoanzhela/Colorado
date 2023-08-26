#include "colorcontainer.h"

ColorContainer::ColorContainer(QObject *parent)
    : QAbstractListModel(parent)
{
    qRegisterMetaType<ColorContainer*>("ColorContainer");
}
int ColorContainer::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_colors.count();
}

QVariant ColorContainer::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0 || index.row() >= m_colors.count())
        return QVariant();

    if (role == ColorRole)
    {
        QVariant colorVariant;
        colorVariant.setValue(m_colors.at(index.row()));
        return colorVariant;
    }

    return QVariant();
}

QHash<int, QByteArray> ColorContainer::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ColorRole] = "color";
    return roles;
}

void ColorContainer::addItem(const QColor &color)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_colors.append(color);
    endInsertRows();
}
