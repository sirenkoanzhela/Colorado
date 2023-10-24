#include "palettemodel.h"

PaletteModel::PaletteModel(QObject *parent)
    : QAbstractListModel(parent)
{
    qRegisterMetaType<PaletteModel*>("PaletteModel*");
}

int PaletteModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // Здесь верните количество элементов в вашей модели
    return 0; // Пример
}

QVariant PaletteModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // В зависимости от роли верните соответствующие данные для элемента с индексом index.row()
    if (role == Qt::DisplayRole) {
        return "Пример данных"; // Пример
    }

    return QVariant();
}

QHash<int, QByteArray> PaletteModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    // Добавьте другие роли, если они есть
    return roles;
}
