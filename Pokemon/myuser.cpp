#include "myuser.h"
#include <QMessageBox>
#include <QtDebug>

myuser::myuser()
{
    user_id = "";
    win_count = 0;
    total_count = 0;
    senior_pkm_medal = 0;
    number_pkm_medal = 0;
    wincount_medal = 0;
    primary_medicine = 0;
    junior_medicine = 0;
    senior_medicine = 0;
    status_medicine = 0;
    money = 0;
}

myuser::myuser(const myuser &sample)
{
    this->user_id = sample.user_id;
    this->win_count = sample.win_count;
    this->total_count = sample.total_count;
    this->senior_pkm_medal = sample.senior_pkm_medal;
    this->number_pkm_medal = sample.number_pkm_medal;
    this->wincount_medal = sample.wincount_medal;
    this->primary_medicine = sample.primary_medicine;
    this->junior_medicine = sample.junior_medicine;
    this->senior_medicine = sample.senior_medicine;
    this->status_medicine = sample.status_medicine;
    this->money = sample.money;
}

myuser myuser::operator=(const myuser &sample)
{
    this->user_id = sample.user_id;
    this->win_count = sample.win_count;
    this->total_count = sample.total_count;
    this->senior_pkm_medal = sample.senior_pkm_medal;
    this->number_pkm_medal = sample.number_pkm_medal;
    this->wincount_medal = sample.wincount_medal;
    this->primary_medicine = sample.primary_medicine;
    this->junior_medicine = sample.junior_medicine;
    this->senior_medicine = sample.senior_medicine;
    this->status_medicine = sample.status_medicine;
    this->money = sample.money;
    return *this;
}

bool myuser::change_money(int change)
{
    if(change>0)
    {
        money += change;
        QString temp = QString("您获得了%1金币").arg(change);
        emit draw_information(temp);
        return true;
    }
    else
    {
        if(change+money>0)
        {
            money -= change;
            return true;
        }
        else
            return false;
    }
}

void myuser::print()
{
    qDebug()<<this->user_id;
    qDebug()<<this->win_count;
    qDebug()<<this->total_count;
    qDebug()<<this->senior_pkm_medal;
    qDebug()<<this->number_pkm_medal;
    qDebug()<<this->wincount_medal;
    qDebug()<<this->primary_medicine;
    qDebug()<<this->junior_medicine;
    qDebug()<<this->senior_medicine;
    qDebug()<<this->status_medicine;
    qDebug()<<this->money;
}
