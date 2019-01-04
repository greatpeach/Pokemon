#ifndef BATTLE_FIELD_H
#define BATTLE_FIELD_H

#include <QWidget>
#include "my_pokemon.h"
#include "myuser.h"

#define EXP_BATTLE 0
#define PKM_BATTLE 1

namespace Ui {
class battle_field;
}

class battle_field : public QWidget
{
    Q_OBJECT

public:
    explicit battle_field(QWidget *parent = nullptr);
    ~battle_field();
    void init(my_pokemon*, my_pokemon*, myuser*, int, int);

private:
    Ui::battle_field *ui;
    my_pokemon* p1;//己方精灵
    my_pokemon* p2;//对方精灵
    myuser *user;//用户信息
    int p1_interval;//己方累积攻击间隔
    int p2_interval;//对方累积攻击间隔
    bool is_auto = 0;//是否自动战斗
    int battletype;//正在进行的战斗类型
    int result;//战斗结果

signals:
    void lose(int, int);

public slots:
    void battle();//战斗主体
    void p1_move();//用户自动战斗
    void p1_move(int, int);//用户自行战斗
    void p2_move();//电脑自动战斗
    void p1_attack();//用户选择攻击
    void p1_skill();//用户选择技能
    void p1_item();//用户选择道具
    void insert_log(QString);
    void end(int);
    void close_battlefield();

};

#endif // BATTLE_FIELD_H
