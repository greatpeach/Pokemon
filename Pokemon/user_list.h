#ifndef USER_LIST_H
#define USER_LIST_H

#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QDebug>
#include <QMouseEvent>
#include "myuser.h"


class user_list : public QTableView
{
    Q_OBJECT

public:
    explicit user_list(QWidget *parent = nullptr);

private:
    QStandardItemModel *model;

public slots:
    void refresh_user(QVector<myuser>, QVector<int>);
    void user_clicked(const QModelIndex &index);

signals:
    void get_pokemonlist(QString user_id);
};

#endif // USER_LIST_H
