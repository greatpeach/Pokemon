#ifndef POKEMON_CENTER_WIDGET_H
#define POKEMON_CENTER_WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include "myuser.h"

namespace Ui {
class pokemon_center_widget;
}

class pokemon_center_widget : public QWidget
{
    Q_OBJECT

public:
    explicit pokemon_center_widget(QWidget *parent = nullptr);
    ~pokemon_center_widget();
    QStandardItemModel *model;
    void refresh_pokemon_center(myuser*);

public slots:
    void buy_item();

signals:
    void update_user();//用于更新用户信息
    void recover();//用于恢复精灵

private slots:
    void on_recover_clicked();

private:
    Ui::pokemon_center_widget *ui;
    myuser *user;
    void closeEvent(QCloseEvent *event);
};

#endif // POKEMON_CENTER_WIDGET_H
