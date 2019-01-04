#include "battle_field.h"
#include "ui_battle_field.h"
#include <windows.h>
#include <QMessageBox>
#include <QInputDialog>

battle_field::battle_field(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battle_field)
{
    ui->setupUi(this);
}

battle_field::~battle_field()
{
    delete ui;
}

void battle_field::init(my_pokemon *user_pkm, my_pokemon *ai_pkm, myuser *user, int battletype, int is_auto)
{
    p1 = user_pkm;
    p2 = ai_pkm;
    p2->recover();
    this->user = user;
    p1_interval = p1->get_speed();
    p2_interval = p2->get_speed();
    this->is_auto = is_auto;
    //设置赛制
    switch (battletype)
    {
    case EXP_BATTLE:
        this->setWindowTitle("升级赛");
        break;

    case PKM_BATTLE:
        this->setWindowTitle("决斗赛");
        break;
    }
    this->battletype = battletype;

    this->ui->skill_btn->setText(p1->get_skillname());//显示p1技能
    switch(p1->get_id())//显示p1图片
    {
    case PIKACHU:
        this->ui->p1_pic->setStyleSheet("border-image: url(:/Pikachu_reverse.png);");
        break;

    case HITOKAGE:
        this->ui->p1_pic->setStyleSheet("border-image: url(:/Hitokage_reverse.png);");
        break;

    case ZENIGAME:
        this->ui->p1_pic->setStyleSheet("border-image: url(:/Zenigame_reverse.png);");
        break;

    case FUSHIGIDANE:
        this->ui->p1_pic->setStyleSheet("border-image: url(:/Fushigidane_reverse.png);");
        break;

    case DEWGONG:
        this->ui->p1_pic->setStyleSheet("border-image: url(:/Dewgong_reverse.png);");
        break;

    case PERORINGA:
        this->ui->p1_pic->setStyleSheet("border-image: url(:/Peroringa_reverse.png);");
        break;
    }

    switch(p2->get_id())//显示p2图片
    {
    case PIKACHU:
        this->ui->p2_pic->setStyleSheet("border-image: url(:/Pikachu.png);");
        break;

    case HITOKAGE:
        this->ui->p2_pic->setStyleSheet("border-image: url(:/Hitokage.png);");
        break;

    case ZENIGAME:
        this->ui->p2_pic->setStyleSheet("border-image: url(:/Zenigame.png);");
        break;

    case FUSHIGIDANE:
        this->ui->p2_pic->setStyleSheet("border-image: url(:/Fushigidane.png);");
        break;

    case DEWGONG:
        this->ui->p2_pic->setStyleSheet("border-image: url(:/Dewgong.png);");
        break;

    case PERORINGA:
        this->ui->p2_pic->setStyleSheet("border-image: url(:/Peroringa.png);");
        break;
    }
    //设置p1血条
    this->ui->p1_hp_bar->setRange(0,p1->get_total_hp());
    this->ui->p1_hp_bar->setValue(p1->get_hp());
    this->ui->p1_hp_bar->setTextVisible(false);
    this->ui->p1_hp->setText(QString::number(p1->get_hp()) + "/" + QString::number(p1->get_total_hp()));
    //设置p2血条
    this->ui->p2_hp_bar->setRange(0,p2->get_total_hp());
    this->ui->p2_hp_bar->setValue(p2->get_hp());
    this->ui->p2_hp_bar->setTextVisible(false);
    this->ui->p2_hp->setText(QString::number(p2->get_hp()) + "/" + QString::number(p2->get_total_hp()));
    //设置战斗日志
    this->ui->log->setReadOnly(true);//设置战斗日志只读
    this->ui->log->insertPlainText("战斗开始\n");
    //设置按钮
    this->ui->attack_btn->setEnabled(false);
    this->ui->skill_btn->setEnabled(false);
    this->ui->item_btn->setEnabled(false);

    connect(p1,SIGNAL(insert_log(QString)),this,SLOT(insert_log(QString)));//p1战斗日志
    connect(p2,SIGNAL(insert_log(QString)),this,SLOT(insert_log(QString)));//p2战斗日志
    connect(this->ui->attack_btn,SIGNAL(clicked()),this,SLOT(p1_attack()));
    connect(this->ui->skill_btn,SIGNAL(clicked()),this,SLOT(p1_skill()));
    connect(this->ui->item_btn,SIGNAL(clicked()),this,SLOT(p1_item()));

    this->show();
    if(!is_auto)
        battle();
    else
    {
        QMessageBox *msg = new QMessageBox(this);
        msg->setIcon(QMessageBox::Information);
        msg->setWindowTitle("提示");
        msg->setText("战斗将自动完成");
        msg->show();
        connect(msg,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(battle()));
    }
}

//插入战斗日志
void battle_field::insert_log(QString log)
{
    this->ui->log->insertPlainText(log);
    this->ui->log->moveCursor(QTextCursor::End);
//    qDebug()<<log;
}

//战斗主体
void battle_field::battle()
{
    qDebug("enter battle");
    int lose_1 = 0, lose_2 = 0;
    //debuff结算
    if (p1->deal_with_debuff())
        lose_1 = 1;
    if (p2->deal_with_debuff())
        lose_2 = 1;

    if (lose_1 && lose_2)
    {
        end(0);//平局
        return;
    }
    else if(lose_1)
    {
        end(1);//p1输
        return;
    }
    else if(lose_2)
    {
        end(2);//p2输
        return;
    }

    if(p1_interval<=p2_interval)
    {
        //玩家回合
        emit insert_log("\n您的回合\n");
        qDebug("p1 turn");
        p1_interval += p1->get_speed();
        if (p1->get_status() == ELECTRICITY)//若麻痹，则跳过此回合
        {
            battle();
            return;
        }

        if(is_auto)
        {
            p1_move();
        }
        else
        {
            this->ui->attack_btn->setEnabled(true);
            ui->attack_btn->setAttribute(Qt::WA_TransparentForMouseEvents, false);
            if(p1->get_remaining_pp())//若pp有剩余，可以使用技能
            {
                this->ui->skill_btn->setEnabled(true);
                ui->skill_btn->setAttribute(Qt::WA_TransparentForMouseEvents, false);
            }
            this->ui->item_btn->setEnabled(true);
            ui->item_btn->setAttribute(Qt::WA_TransparentForMouseEvents, false);
        }
    }
    else
    {
        //对方回合
        emit insert_log("\n对方的回合\n");
        qDebug("p2 turn");
        p2_interval += p2->get_speed();
        if (p2->get_status() == ELECTRICITY)//若麻痹，则跳过此回合
        {
            battle();
            return;
        }
        p2_move();
    }
}

//用户自动战斗
void battle_field::p1_move()
{
    int lose = 0;
    int manipulate = random_num_generator(0.7);//自动获取操作，0.3概率普通攻击,0.7概率使用技能
    if (!p1->get_remaining_pp())//pp不足只能普通攻击
        manipulate = 0;
    bullet *bul;

    switch (manipulate)
    {
    case 0://普通攻击
        bul = p1->attack();
        lose = p2->hit(bul);
        break;

    case 1://使用技能
        bul = p1->skill();
        lose = p2->hit(bul);
        break;
    }
    if(lose)
    {
        end(2);
        return;
    }
    //更新血量
    this->ui->p1_hp_bar->setValue(p1->get_hp());
    this->ui->p1_hp->setText(QString::number(p1->get_hp())+"/"+QString::number(p1->get_total_hp()));
    this->ui->p2_hp_bar->setValue(p2->get_hp());
    this->ui->p2_hp->setText(QString::number(p2->get_hp())+"/"+QString::number(p2->get_total_hp()));
    qDebug("更新血量");
    Sleep(1000);
    battle();//继续战斗
}

//用户手动战斗
void battle_field::p1_move(int manipulate, int medicine)
{
    //操作结束，按钮失效
    this->ui->attack_btn->setEnabled(false);
    this->ui->skill_btn->setEnabled(false);
    this->ui->item_btn->setEnabled(false);
    ui->attack_btn->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->skill_btn->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->item_btn->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    int lose = 0;
    bullet *bul;
    switch (manipulate)
    {
    case 0://普通攻击
        bul = p1->attack();
        lose = p2->hit(bul);
        break;

    case 1://技能
        bul = p1->skill();
        lose = p2->hit(bul);
        break;

    case 2://使用道具
        switch (medicine)
        {
        case 0://伤药
            p1->hp_recover(0.1);
            user->primary_medicine--;
            break;

        case 1://好伤药
            p1->hp_recover(0.2);
            user->junior_medicine--;
            break;

        case 2://超好伤药
            p1->hp_recover(0.3);
            user->senior_medicine--;
            break;

        case 3://异常状态恢复药
            p1->debuff_recover();
            user->status_medicine--;
            break;
        }
    }

    if(lose)
    {
        end(2);
        return;
    }

    //更新血量
    this->ui->p1_hp_bar->setValue(p1->get_hp());
    this->ui->p1_hp->setText(QString::number(p1->get_hp())+"/"+QString::number(p1->get_total_hp()));
    this->ui->p2_hp_bar->setValue(p2->get_hp());
    this->ui->p2_hp->setText(QString::number(p2->get_hp())+"/"+QString::number(p2->get_total_hp()));
    Sleep(1000);
    battle();//继续战斗
}

//电脑自动战斗
void battle_field::p2_move()
{
    int lose = 0;
    int manipulate = random_num_generator(0.7);//自动获取操作，0.3概率普通攻击,0.7概率使用技能
    if (!p2->get_remaining_pp())
        manipulate = 0;
    bullet *bul;
    switch (manipulate)
    {
    case 0://普通攻击
        bul = p2->attack();
        lose = p1->hit(bul);
        break;

    case 1://技能
        bul = p2->skill();
        lose = p1->hit(bul);
        break;
    }
    if(lose)
    {
        end(1);
        return;
    }
    this->ui->p1_hp_bar->setValue(p1->get_hp());
    this->ui->p1_hp->setText(QString::number(p1->get_hp())+"/"+QString::number(p1->get_total_hp()));
    this->ui->p2_hp_bar->setValue(p2->get_hp());
    this->ui->p2_hp->setText(QString::number(p2->get_hp())+"/"+QString::number(p2->get_total_hp()));
    Sleep(1000);
    battle();//继续战斗
}

//p1普通攻击
void battle_field::p1_attack()
{
    p1_move(0, 0);
}

//p1技能
void battle_field::p1_skill()
{
    p1_move(1, 0);
}

//p1道具
void battle_field::p1_item()
{
    QStringList list;
    if(user->primary_medicine)
        list<<tr("伤药");
    if(user->junior_medicine)
        list<<tr("好伤药");
    if(user->senior_medicine)
        list<<tr("超好伤药");
    if(user->status_medicine)
        list<<tr("异常状态恢复药");
    bool ok;
    QString item = QInputDialog::getItem(this,tr("使用物品"),tr("请选择你要使用的物品"),list, 0, false, &ok);
    if(ok)
    {
        if(item=="伤药")
            p1_move(2, 0);
        else if(item=="好伤药")
            p1_move(2, 1);
        else if(item=="超好伤药")
            p1_move(2, 2);
        else if(item=="异常状态恢复药")
            p1_move(2, 3);
    }
}

//结束处理
void battle_field::end(int lose)
{
    this->ui->p1_hp_bar->setValue(p1->get_hp());
    this->ui->p1_hp->setText(QString::number(p1->get_hp())+"/"+QString::number(p1->get_total_hp()));
    this->ui->p2_hp_bar->setValue(p2->get_hp());
    this->ui->p2_hp->setText(QString::number(p2->get_hp())+"/"+QString::number(p2->get_total_hp()));
    this->ui->attack_btn->setEnabled(false);
    this->ui->skill_btn->setEnabled(false);
    this->ui->item_btn->setEnabled(false);
    disconnect(this->ui->attack_btn,SIGNAL(clicked()),this,SLOT(p1_attack()));
    disconnect(this->ui->skill_btn,SIGNAL(clicked()),this,SLOT(p1_skill()));
    Sleep(1000);

    result = lose;
    QString temp;
    QMessageBox *msg = new QMessageBox;
    msg->setIcon(QMessageBox::Information);
    switch(lose)
    {
    case 2://玩家获胜
        temp = "您获得了胜利！";
        msg->setWindowTitle("恭喜");
        msg->setText(temp);
        break;

    case 1://玩家失败
        temp = "您失败了。";
        msg->setWindowTitle("很遗憾");
        msg->setText(temp);
        break;

    case 0://平局
        temp = "平局！";
        msg->setWindowTitle("巧了嘿");
        msg->setText(temp);
        break;
    }
    msg->show();
    connect(msg,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(close_battlefield()));
}

void battle_field::close_battlefield()
{
    this->close();
    emit lose(result, battletype);
}
