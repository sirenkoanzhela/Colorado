#ifndef USERPAGE_H
#define USERPAGE_H

#include <QObject>
static QString DEFAULT_COLOR_NAME = "black";
static QString DEFAULT_COLOR_HEX = "#000000";

class UserPage : public QObject
{
    Q_OBJECT
public:
    explicit UserPage(QObject *parent = nullptr);

    void get_info(int id);

    void set_color_name(QString);
    void set_color_hex(QString);

    QString get_color_name();
    QString get_color_hex();

signals:
private:
    QString m_color_name = DEFAULT_COLOR_NAME;
    QString m_color_hex = DEFAULT_COLOR_HEX;
};

#endif // USERPAGE_H
