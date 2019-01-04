#include "pokemon_center_widget.h"
#include "ui_pokemon_center_widget.h"
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>

pokemon_center_widget::pokemon_center_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pokemon_center_widget)
{
    model = new QStandardItemModel;
    model->setRowCount(4);
    model->setHeaderData(0,Qt::Vertical, "伤药");
    model->setHeaderData(1,Qt::Vertical, "好伤药");
    model->setHeaderData(2,Qt::Vertical, "超好伤药");
    model->setHeaderData(3,Qt::Vertical, "异常状态恢复药");

    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal, "持有个数");
    model->setHeaderData(1,Qt::Horizontal, "价格");
    model->setHeaderData(2,Qt::Horizontal, "购买");
    ui->setupUi(this);
    this->hide();
}

pokemon_center_widget::~pokemon_center_widget()
{
    delete ui;
}

void pokemon_center_widget::refresh_pokemon_center(myuser *user)
{
    this->user = user;
    QStandardItem *temp;
    temp = new QStandardItem(QString::number(user->primary_medicine));
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(0, 0, temp);
    temp = new QStandardItem("20");
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(0, 1, temp);

    temp = new QStandardItem(QString::number(user->junior_medicine));
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(1, 0,temp);
    temp = new QStandardItem("50");
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(1, 1, temp);

    temp = new QStandardItem(QString::number(user->senior_medicine));
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(2, 0, temp);
    temp = new QStandardItem("100");
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(2, 1, temp);

    temp = new QStandardItem(QString::number(user->status_medicine));
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(3, 0, temp);
    temp = new QStandardItem("50");
    temp->setTextAlignment(Qt::AlignCenter);
    model->setItem(3, 1, temp);

    for(int i=0;i<4;i++)
    {
        QPushButton *but = new QPushButton("购买");
        but->setProperty("row",i);
        this->ui->shop->setIndexWidget(model->index(i,2),but);
        connect(but,SIGNAL(clicked()),this,SLOT(buy_item()));
    }

    this->ui->shop->setModel(model);
    this->ui->shop->setColumnWidth(0,80);
    this->ui->shop->setColumnWidth(1,50);
    this->ui->shop->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    this->ui->shop->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    this->ui->shop->setAlternatingRowColors(true);
    this->ui->money->setText(QString::number(user->money));
    this->show();

}

void pokemon_center_widget::buy_item()
{
    QPushButton *btn = (QPushButton *)sender();
    int row = btn->property("row").toInt();
    QStandardItem *temp;
    switch(row)
    {
    case 0://购买伤药
        if(user->money>=20)
        {
            user->primary_medicine++;
            temp = new QStandardItem(QString::number(user->primary_medicine));
            temp->setTextAlignment(Qt::AlignCenter);
            model->setItem(0, 0, temp);
            user->money -= 20;
            this->ui->money->setText(QString::number(user->money));
        }
        else
            QMessageBox::information(this, "购买失败", "您的剩余金币不足20");
        break;

    case 1://购买好伤药
        if(user->money>=50)
        {
            user->junior_medicine++;
            temp = new QStandardItem(QString::number(user->junior_medicine));
            temp->setTextAlignment(Qt::AlignCenter);
            model->setItem(1, 0, temp);
            user->money -= 50;
            this->ui->money->setText(QString::number(user->money));
        }
        else
            QMessageBox::information(this, "购买失败", "您的剩余金币不足50");
        break;

    case 2://购买超好伤药
        if(user->money>=100)
        {
            user->senior_medicine++;
            temp = new QStandardItem(QString::number(user->senior_medicine));
            temp->setTextAlignment(Qt::AlignCenter);
            model->setItem(2, 0, temp);
            user->money -= 100;
            this->ui->money->setText(QString::number(user->money));
        }
        else
            QMessageBox::information(this, "购买失败", "您的剩余金币不足100");
        break;

    case 3://购买状态恢复药
        if(user->money>=50)
        {
            user->status_medicine++;
            temp = new QStandardItem(QString::number(user->status_medicine));
            temp->setTextAlignment(Qt::AlignCenter);
            model->setItem(3, 0, temp);
            user->money -= 50;
            this->ui->money->setText(QString::number(user->money));
        }
        else
            QMessageBox::information(this, "购买失败", "您的剩余金币不足50");
        break;
    }
}

//关闭窗口时更新用户信息
void pokemon_center_widget::closeEvent(QCloseEvent *event)
{
    emit update_user();
    event->accept();
}

void pokemon_center_widget::on_recover_clicked()
{
    QMessageBox::information(this, "恢复成功", "您的精灵体力全都恢复啦！");
    emit recover();
}
