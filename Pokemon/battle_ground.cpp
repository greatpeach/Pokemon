#include "battle_ground.h"
#include "ui_battle_ground.h"
#include <QInputDialog>

battle_ground::battle_ground(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battle_ground)
{
    ui->setupUi(this);
    this->hide();

    connect(this->ui->exp_battle,SIGNAL(clicked()),this,SLOT(start_exp_battle()));
    connect(this->ui->pkm_battle,SIGNAL(clicked()),this,SLOT(start_pkm_battle()));
    connect(this->ui->auto_check,SIGNAL(stateChanged(int)),this,SLOT(set_auto(int)));

    model1 = new QStandardItemModel(this);
    model1->setColumnCount(2);
    model1->setHeaderData(0,Qt::Horizontal, "精灵");
    model1->setHeaderData(1,Qt::Horizontal, "lv");
    this->ui->user_list->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    this->ui->user_list->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    this->ui->user_list->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);//只能选中单行
    this->ui->user_list->setAlternatingRowColors(true);
    connect(this->ui->user_list,SIGNAL(clicked(const QModelIndex&)),this,SLOT(user_list_clicked(const QModelIndex&)));//返回点中用户索引
    this->ui->user_list->verticalHeader()->hide();

    model2 = new QStandardItemModel(this);
    model2->setColumnCount(2);
    model2->setHeaderData(0,Qt::Horizontal, "精灵");
    model2->setHeaderData(1,Qt::Horizontal, "lv");
    this->ui->server_list->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    this->ui->server_list->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    this->ui->server_list->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);//只能选中单行
    this->ui->server_list->setAlternatingRowColors(true);
    connect(this->ui->server_list,SIGNAL(clicked(const QModelIndex&)),this,SLOT(server_list_clicked(const QModelIndex&)));//返回点中用户索引
    this->ui->server_list->verticalHeader()->hide();
}

void battle_ground::show_battleground(QList<my_pokemon*> *pkm_list, QList<my_pokemon*> *server_list, myuser *user)
{
    this->pkm_list = pkm_list;
    this->server_list = server_list;
    this->user = user;
    model1->removeRows(0,model1->rowCount());//清空原有用户信息
    model2->removeRows(0,model2->rowCount());//清空原有服务器精灵信息

    QStandardItem *temp;
    for(int i=0;i<pkm_list->size();i++)
    {
        temp = new QStandardItem(pkm_list->at(i)->get_name());
        temp->setTextAlignment(Qt::AlignHCenter);
        model1->setItem(i, 0, temp);

        temp = new QStandardItem(QString::number(pkm_list->at(i)->get_level()));
        temp->setTextAlignment(Qt::AlignHCenter);
        model1->setItem(i, 1, temp);
    }
    this->ui->user_list->setModel(model1);
    this->ui->user_list->show();

    for(int i=0;i<server_list->size();i++)
    {
        temp = new QStandardItem(server_list->at(i)->get_name());
        temp->setTextAlignment(Qt::AlignHCenter);
        model2->setItem(i, 0, temp);

        temp = new QStandardItem(QString::number(server_list->at(i)->get_level()));
        temp->setTextAlignment(Qt::AlignHCenter);
        model2->setItem(i, 1, temp);
    }
    this->ui->server_list->setModel(model2);
    this->ui->server_list->show();

    if(!pkm_list->size())
        p1 = NULL;
    else
        p1 = pkm_list->at(0);
    p2 = server_list->at(0);

    this->show();
}

battle_ground::~battle_ground()
{
    delete ui;
}

QList<int> battle_ground::get_random_num(int max)
{
   int pkm[3] = {0, 0, 0};
   pkm[0] = rand() % max;
   int temp;
   while(!(pkm[1]&&pkm[2]))
   {
       temp = rand() % max;
       if(!pkm[1])
           if(temp==pkm[0])
               continue;
           else
               pkm[1] = temp;
       else
           if(temp==pkm[0]||temp==pkm[1])
               continue;
           else
               pkm[2] = temp;
   }
   QList<int> list;
   list.append(pkm[0]);
   list.append(pkm[1]);
   list.append(pkm[2]);
   return list;
}

//选择出战精灵
void battle_ground::user_list_clicked(const QModelIndex &index)
{
    p1 = pkm_list->at(index.row());
}

//选择对方精灵
void battle_ground::server_list_clicked(const QModelIndex &index)
{
    p2 = server_list->at(index.row());
}

void battle_ground::start_exp_battle()
{
    mybattlefield = new battle_field;
    connect(mybattlefield,SIGNAL(lose(int, int)),this,SLOT(account(int, int)));//结束信号
    mybattlefield->init(p1, p2, user, EXP_BATTLE, is_auto);
}

void battle_ground::start_pkm_battle()
{
    mybattlefield = new battle_field;
    connect(mybattlefield,SIGNAL(lose(int, int)),this,SLOT(account(int, int)));//结束信号
    mybattlefield->init(p1, p2, user, PKM_BATTLE, is_auto);
}

//升级
void battle_ground::lv_up(int pre_lv)
{
    QString msg = "您的 %1 升级到 %2 了";
    QMessageBox::information(this,"恭喜",msg.arg(p1->get_name()).arg(pre_lv+1));
}
//设置自动战斗
void battle_ground::set_auto(int state)
{
    if(state == Qt::Checked)
        this->is_auto = true;
    else
        this->is_auto = false;
}

//判断是否能获得高级精灵奖章
void battle_ground::senior_pkm_count()
{
    int count = 0;
    for(int i=0;i<pkm_list->size();i++)
    {
        if(pkm_list->at(i)->get_level()==15)
            count++;
    }
    switch(count)
    {
    case 5:
        if(user->senior_pkm_medal<1)
        {
            user->senior_pkm_medal=1;
            QMessageBox::information(this,"恭喜","您获得了高级精灵铜奖章");
        }
        break;

    case 10:
        if(user->senior_pkm_medal<2)
        {
            user->senior_pkm_medal=2;
            QMessageBox::information(this,"恭喜","您获得了高级精灵银奖章");
        }
        break;

    case 15:
        if(user->senior_pkm_medal<3)
        {
            user->senior_pkm_medal=3;
            QMessageBox::information(this,"恭喜","您获得了高级精灵金奖章");
        }
        break;
    }
}

//判断是否能获得胜场奖章
void battle_ground::wincount_medal_count()
{
    switch(user->win_count)
    {
    case 5:
        user->wincount_medal = 1;//获得胜场铜奖章
        QMessageBox::information(this,"恭喜","您获得了胜场铜奖章");
        break;

    case 10:
        user->wincount_medal = 2;//获得胜场银奖章
        QMessageBox::information(this,"恭喜","您获得了胜场银奖章");
        break;

    case 15:
        user->wincount_medal = 3;//获得胜场金奖章
        QMessageBox::information(this,"恭喜","您获得了胜场金奖章");
        break;
    }
}

//判断能否获得精灵收集奖章
void battle_ground::pkm_count()
{
    switch(pkm_list->size()+1)
    {
    case 5:
        if(user->number_pkm_medal<1)
        {
            user->number_pkm_medal=1;
            QMessageBox::information(this,"恭喜","您获得了精灵收集铜奖章");
        }
        break;

    case 10:
        if(user->number_pkm_medal<2)
        {
            user->number_pkm_medal=2;
            QMessageBox::information(this,"恭喜","您获得了精灵收集银奖章");
        }
        break;

    case 15:
        if(user->number_pkm_medal<3)
        {
            user->number_pkm_medal=3;
            QMessageBox::information(this,"恭喜","您获得了精灵收集金奖章");
        }
        break;
    }
}

//结算
void battle_ground::account(int lose, int battletype)
{
    QString temp;
    if(lose == 2|| lose == 0)//若玩家胜利，经验值奖章结算
    {
        connect(p1,SIGNAL(lv_up(int)),this,SLOT(lv_up(int)));
        int exp = p2->get_level()*p2->get_level()*2;//经验获取为对方精灵等级平方乘2
        temp = "您的精灵获得了 %1 经验";
        QMessageBox::information(this,"恭喜",temp.arg(exp));
        p1->get_exp(exp);
        disconnect(p1,SIGNAL(lv_up(int)),this,SLOT(lv_up(int)));
        user->total_count++;
        user->win_count++;
        senior_pkm_count();
        wincount_medal_count();
    }
    else//玩家失败经验结算
    {
        connect(p1,SIGNAL(lv_up(int)),this,SLOT(lv_up(int)));
        int exp = p2->get_level()*p2->get_level();//获取经验为胜利时的一半
        temp = "您没能获胜。您的精灵获得了 %1 经验";
        QMessageBox::information(this,"很遗憾",temp.arg(exp));
        p1->get_exp(exp);
        disconnect(p1,SIGNAL(lv_up(int)),this,SLOT(lv_up(int)));
        senior_pkm_count();
        user->total_count++;
        p1->hp1();//回复到1血
    }
    emit update_pkm(CHANGE_PKM, 0, p1->to_pkmcontainer());//更新p1信息

    if(battletype==PKM_BATTLE)//若为决斗赛
    {
        qDebug("pkm_battle");
        if(lose==0||lose==2)//玩家胜利奖励精灵
        {
            my_pkm_container null;
            QMessageBox::information(this,"恭喜","您获得了一只精灵");
            emit update_pkm(NEW_PKM, p2->get_id(), null);
            pkm_count();
        }
        else//玩家失败删除三只
        {
            if(pkm_list->size()>3)//若剩余大于3，随机选3只，选一只送出
            {
                QList<int> list = get_random_num(pkm_list->size());
                QStringList stringlist;
                for(int i=0;i<3;i++)
                {
                    my_pokemon *tmp = pkm_list->at(list[i]);
                    QByteArray str;
                    str = tmp->get_name().toUtf8();
                    str += "-" + QByteArray::number(tmp->get_level());
                    str += "级";
                    stringlist << tr(str);
                }
                bool ok;
                QString ban = QInputDialog::getItem(this,tr("送出"),tr("请选择你要送出的精灵"),stringlist, 0, false, &ok);
                for(int i=0;i<3;i++)
                {
                    if(stringlist[i]==ban)
                    {
                        int pos = list[i];
                        QMessageBox::information(this,"送出","送出了"+pkm_list->at(pos)->get_name());
                        my_pkm_container temp;
                        emit update_pkm(DELETE_PKM, pkm_list->at(pos)->get_num(),temp);
                        pkm_list->removeAt(pos);
                        model1->removeRow(pos);
                        break;
                    }
                }
            }
            else//若小于等于3在剩余所有中选一只送出
            {
                QStringList stringlist;
                for(int i=0;i<pkm_list->size();i++)
                {
                    QByteArray str;
                    str = pkm_list->at(i)->get_name().toUtf8();
                    str += "-" + QByteArray::number(pkm_list->at(i)->get_level());
                    str += "级";
                    stringlist << tr(str);
                }
                bool ok;
                QString ban = QInputDialog::getItem(this,tr("送出"),tr("请选择你要送出的精灵"),stringlist, 0, false, &ok);
                for(int i=0;i<pkm_list->size();i++)
                {
                    if(stringlist[i]==ban)
                    {
                        QMessageBox::information(this,"送出","送出了"+pkm_list->at(i)->get_name());
                        my_pkm_container temp;
                        emit update_pkm(DELETE_PKM, pkm_list->at(i)->get_num(),temp);
                        pkm_list->removeAt(i);
                        model1->removeRow(i);
                        break;
                    }
                }
                //判断是否还有精灵
                if(!pkm_list->size())
                {
                    my_pkm_container null;
                    int ran = rand()%6+1;
                    QMessageBox::information(this,"别灰心","我们又送给您一只精灵，请在背包中查看");
                    emit update_pkm(NEW_PKM, ran, null);
                }
            }
        }
    }

    emit update_user();//更新用户信息
    p2->recover();
}

void battle_ground::on_go_back_clicked()
{
    this->close();
}
