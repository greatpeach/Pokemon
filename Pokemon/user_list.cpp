#include "user_list.h"
//用户列表界面

user_list::user_list(QWidget *parent) :
    QTableView (parent)
{
    model = new QStandardItemModel(this);

    model->setColumnCount(7);
    model->setHeaderData(0,Qt::Horizontal, "用户");
    model->setHeaderData(1,Qt::Horizontal, "登录状态");
    model->setHeaderData(2,Qt::Horizontal, "胜场");
    model->setHeaderData(3,Qt::Horizontal, "胜率");
    model->setHeaderData(4,Qt::Horizontal, "高级精灵奖章");
    model->setHeaderData(5,Qt::Horizontal, "精灵收集者奖章");
    model->setHeaderData(6,Qt::Horizontal, "决斗赛胜者奖章");


    this->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    this->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);//只能选中单行
    this->setAlternatingRowColors(true);
    this->verticalHeader()->hide();
    connect(this,SIGNAL(clicked(const QModelIndex&)),this,SLOT(user_clicked(const QModelIndex&)));//返回点中用户索引
    this->setColumnWidth(0,150);
    this->setColumnWidth(1,90);
    this->setColumnWidth(2,40);
    this->setColumnWidth(3,40);
    this->setColumnWidth(4,90);
    this->setColumnWidth(5,90);
    this->setColumnWidth(6,90);

    this->hide();
}

//更新用户信息
void user_list::refresh_user(QVector<myuser> user_list, QVector<int> online_status)
{
    model->removeRows(0,model->rowCount());//清空原有用户信息
    QStandardItem *temp;
    for(int i = 0; i < user_list.size(); i++)
    {
        model->setItem(i, 0, new QStandardItem(user_list.at(i).user_id));
        if(online_status.at(i))
        {
            QStandardItem *online = new QStandardItem("Online");
            online->setTextAlignment(Qt::AlignHCenter);
            model->setItem(i, 1, online);
        }
        else
        {
            QStandardItem *offline = new QStandardItem("Offline");
            offline->setTextAlignment(Qt::AlignHCenter);
            model->setItem(i, 1, offline);
        }

        temp = new QStandardItem(QString::number(user_list[i].win_count));
        temp->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 2, temp);

        if(user_list[i].total_count!=0)
        {
            double rate = 100*user_list[i].win_count/user_list[i].total_count;
            temp = new QStandardItem(QString::number(rate)+"%");
        }
        else
            temp = new QStandardItem("0%");
        temp->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 3, temp);

        switch(user_list[i].senior_pkm_medal)
        {
        case 0:
            temp = new QStandardItem("无");
            break;

        case 1:
            temp = new QStandardItem("铜");
            break;

        case 2:
            temp = new QStandardItem("银");
            break;

        case 3:
            temp = new QStandardItem("金");
            break;
        }
        temp->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 4, temp);


        switch(user_list[i].number_pkm_medal)
        {
        case 0:
            temp = new QStandardItem("无");
            break;

        case 1:
            temp = new QStandardItem("铜");
            break;

        case 2:
            temp = new QStandardItem("银");
            break;

        case 3:
            temp = new QStandardItem("金");
            break;
        }
        temp->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 5, temp);

        switch(user_list[i].wincount_medal)
        {
        case 0:
            temp = new QStandardItem("无");
            break;

        case 1:
            temp = new QStandardItem("铜");
            break;

        case 2:
            temp = new QStandardItem("银");
            break;

        case 3:
            temp = new QStandardItem("金");
            break;
        }
        temp->setTextAlignment(Qt::AlignHCenter);
        model->setItem(i, 6, temp);
    }
    this->setModel(model);
    this->setSortingEnabled(true);
    this->sortByColumn(1,Qt::DescendingOrder);
    this->show();
}

//获取某一用户的精灵信息
void user_list::user_clicked(const QModelIndex &index)
{
//    qDebug()<<model->item(index.row(),0)->text();
    emit get_pokemonlist(model->item(index.row(),0)->text());
}
