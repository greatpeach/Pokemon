#include "myuser.h"
#include <QDebug>

myuser::myuser()
{
    user_id = "";
    user_password = "";
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

void myuser::print()
{
    qDebug()<<this->user_id;
    qDebug()<<this->user_password;
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
