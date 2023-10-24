#ifndef PALETTEMODEL_H
#define PALETTEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QColor>

class PaletteModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PaletteModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
private:
    QVector<QColor> m_colors;
};

#endif // PALETTEMODEL_H
