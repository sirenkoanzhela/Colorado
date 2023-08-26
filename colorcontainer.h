#ifndef COLORCONTAINER_H
#define COLORCONTAINER_H


#include <QAbstractListModel>
#include <QColor>

class ColorContainer : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ColorContainer(QObject *parent = nullptr);
    enum Role {
        ColorRole = Qt::UserRole + 1,
    };
    Q_ENUM(Role)
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void addItem(const QColor &color);
private:
    QList<QColor> m_colors;
};

#endif // COLORCONTAINER_H
