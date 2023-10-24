#include "palettemodel.h"

PaletteModel::PaletteModel(QObject *parent)
    : QAbstractListModel(parent)
{
    qRegisterMetaType<PaletteModel*>("PaletteModel*");
}

int PaletteModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;
}

QVariant PaletteModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        return "Пример данных"; // Пример
    }

    return QVariant();
}

QHash<int, QByteArray> PaletteModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    return roles;
}
