#ifndef _POKEMON_H_
#define _POKEMON_H_
#include <QString>
#include <QDebug>

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

//id
#define PIKACHU 1
#define HITOKAGE 2
#define ZENIGAME 3
#define FUSHIGIDANE 4
#define DEWGONG 5
#define PERORINGA 6


class my_pokemon
{
public:
    my_pokemon();
    my_pokemon(my_pokemon &);
    my_pokemon(int, int, QString);//通过id创建一只1级的精灵
    void print();

    int num;//每个精灵唯一的身份标识
    int id;
    QString name;
    int level;
    int exp;

    int hp;
    int power;//攻击力
    int defence;//防御力
    int attack_interval;//攻击间隔
    QString user_id;//主人
};

#endif

