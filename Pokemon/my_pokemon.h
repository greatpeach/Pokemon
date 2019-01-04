#ifndef _POKEMON_H_
#define _POKEMON_H_
#include <QString>
#include <QDebug>
#include <QObject>


//pokemon category
#define ATTACK 1
#define TANK 2
#define DEFENCE 3
#define SPEED 4

//element category
#define NORMAL 0
#define CRITICAL 1
#define ELECTRICITY 2
#define FIRE 3
#define WATER 4
#define GRASS 5

#define PIKACHU 1
#define HITOKAGE 2
#define ZENIGAME 3
#define FUSHIGIDANE 4
#define DEWGONG 5
#define PERORINGA 6


int random_num_generator(double);

class bullet
{
public:
    bullet();
    bullet(const bullet &sample);
    void operator=(const bullet &sample);

    int total_damage;//基础伤害
    int element_damage;//属性异常状态
    int element;//攻击属性
};

class my_pkm_container;

class my_pokemon : public QObject
{
    Q_OBJECT
public:
    my_pokemon();
    void if_level_up();//是否能够升级
    bullet* attack();//普通攻击
    virtual bullet* skill() = 0;//使用技能
    bool hit(bullet*);//受到攻击
    void hp_recover(double);//使用回复药
    void debuff_recover();//恢复异常状态
    void recover();//完全恢复
    int get_speed()
    {
        return attack_interval;
    }

    int get_hp()
    {
        return remaining_hp;
    }

    int get_total_hp(){return total_hp;}

    QString get_name()
    {
        return name;
    }

    int get_remaining_pp()
    {
        return remaining_pp;
    }

    int get_status()
    {
        return status;
    }

    void rename(QString new_name)
    {
        this->name = new_name;
    }

    int get_num()
    {
        return num;
    }

    int get_id()
    {
        return id;
    }

    int get_level(){return level;}

    int get_exp(){return exp;}

    int get_power(){return power;}

    int get_defence(){return defence;}

    QString get_skillname(){return skill_name;}

    my_pkm_container to_pkmcontainer();

    void print();
    int deal_with_debuff();
    void get_exp(int);//获取经验值
    void hp1(){this->remaining_hp = 1;}//从0回复到1点血

protected:
    virtual void level_up() = 0;
    void level_up_for_all();
    int num;//精灵的唯一标识
    int id;//精灵种类
    QString name;
    int attribute;//精灵类别
    int element;//精灵属性
    int level;
    int exp;

    int total_hp;
    int remaining_hp;
    int power;//攻击力
    int defence;//防御力
    int attack_interval;//攻击间隔
    int status;//精灵状态（是否属性异常）
    int remaining_chaos_time;//状态异常剩余时间
    int total_pp;//技能使用次数
    int remaining_pp;//剩余技能使用次数
    int total_power;//用于恢复到原攻击力
    int total_defence;//用于恢复到原防御力
    QString skill_name;//技能名称

signals:
    void insert_log(QString);
    void lv_up(int);//升级信号
};

//主类
//敏捷型
class my_Speed : public my_pokemon
{
public:
    my_Speed();

protected:
    void level_up();
};

//攻击型
class my_Attack : public my_pokemon
{
public:
    my_Attack();

protected:
    void level_up();
};

//防御性
class my_Defence : public my_pokemon
{
public:
    my_Defence();

protected:
    void level_up();
};

//肉盾型
class my_Tank : public my_pokemon
{
public:
    my_Tank();

protected:
    void level_up();
};


//皮卡丘
class my_Pikachu : public my_Speed
{
public:
    bullet* skill();
    my_Pikachu(int level);
    my_Pikachu(int, int, QString, int, int, int, int, int, int);
};

//小火龙
class my_Hitokage : public my_Attack
{
public:
    bullet* skill();
    my_Hitokage(int level);
    my_Hitokage(int, int, QString, int, int, int, int, int, int);
};

//杰尼龟
class my_Zenigame : public my_Attack
{
public:
    bullet* skill();
    my_Zenigame(int level);
    my_Zenigame(int, int, QString, int, int, int, int, int, int);
};

//妙蛙种子
class my_Fushigidane : public my_Tank
{
public:
    bullet* skill();
    my_Fushigidane(int level);
    my_Fushigidane(int, int, QString, int, int, int, int, int, int);
};

//白海狮
class my_Dewgong : public my_Tank
{
public:
    bullet* skill();
    my_Dewgong(int level);
    my_Dewgong(int, int, QString, int, int, int, int, int, int);
};

//大舌头
class my_Peroringa : public my_Defence
{
public:
    bullet* skill();
    my_Peroringa(int level);
    my_Peroringa(int, int, QString, int, int, int, int, int, int);
};

class my_pkm_container
{
public:
    my_pkm_container(){}
    my_pkm_container(int, int, QString, int, int, int, int, int, int);
    my_pkm_container(const my_pkm_container &);
    my_pkm_container operator=(const my_pkm_container &);
    QByteArray toByteArray();
    void print();

    int num;//精灵的唯一标识
    int id;//精灵种类
    QString name;
    int attribute;//精灵类别
    int element;//精灵属性
    int level;
    int exp;

    int total_hp;
    int remaining_hp;
    int power;//攻击力
    int defence;//防御力
    int attack_interval;//攻击间隔
    int status;//精灵状态（是否属性异常）
    int remaining_chaos_time;//状态异常剩余时间
    int total_pp;//技能使用次数
    int remaining_pp;//剩余技能使用次数
    int total_power;//用于恢复到原攻击力
    int total_defence;//用于恢复到原防御力
    QString skill_name;//技能名称
};

#endif

