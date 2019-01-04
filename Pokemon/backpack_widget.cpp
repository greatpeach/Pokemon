#include "backpack_widget.h"


mybackpack::mybackpack(QWidget *parent) :
    QTableView (parent)
{
    model = new QStandardItemModel(this);

    model->setRowCount(5);
    model->setHeaderData(0,Qt::Vertical, "伤药");
    model->setHeaderData(1,Qt::Vertical, "好伤药");
    model->setHeaderData(2,Qt::Vertical, "超好伤药");
    model->setHeaderData(3,Qt::Vertical, "异常状态恢复药");
    model->setHeaderData(4,Qt::Vertical, "钱");

    this->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    this->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);//只能选中单行
    this->setAlternatingRowColors(true);
    this->horizontalHeader()->hide();
    this->setWindowTitle("我的背包");
    this->setMinimumSize(300,200);
    this->setMaximumSize(300,200);
    this->hide();

}

void mybackpack::refresh_mybackpack(myuser user)
{
    model->removeColumn(0);
    QStandardItem *temp;
    temp = new QStandardItem(QString::number(user.primary_medicine));
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(0, 0, temp);

    temp = new QStandardItem(QString::number(user.junior_medicine));
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(1, 0,temp);

    temp = new QStandardItem(QString::number(user.senior_medicine));
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(2, 0, temp);

    temp = new QStandardItem(QString::number(user.status_medicine));
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(3, 0, temp);

    temp = new QStandardItem(QString::number(user.money));
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(4, 0, temp);

    this->setModel(model);
    this->setColumnWidth(0,200);
    this->show();
}
