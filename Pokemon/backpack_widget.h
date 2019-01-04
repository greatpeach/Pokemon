#ifndef BACKPACK_WIDGET_H
#define BACKPACK_WIDGET_H

#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QDebug>
#include "myuser.h"

class mybackpack: public QTableView
{
    Q_OBJECT

public:
    explicit mybackpack(QWidget *parent = nullptr);

private:
    QStandardItemModel *model;

public slots:
    void refresh_mybackpack(myuser);

};

#endif // BACKPACK_WIDGET_H
