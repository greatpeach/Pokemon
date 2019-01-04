#include "my_pokemon.h"

my_pokemon::my_pokemon()
{

}

my_pokemon::my_pokemon(my_pokemon &sample)
{
    num = sample.num;
    id = sample.id;
    name = sample.name;
    level = sample.level;
    exp = sample.exp;
    hp = sample.hp;
    power = sample.power;
    defence = sample.defence;
    attack_interval = sample.attack_interval;
    user_id = sample.user_id;
}

my_pokemon::my_pokemon(int id, int num, QString user_id)
{
    qDebug()<<"id=" <<id;
    this->num = num;
    level = 1;
    exp = 0;
    hp = 300;
    power = 30;
    defence = 30;
    attack_interval = 500;
    this->user_id = user_id;
    this->id = id;
    switch (id)
    {
    case PIKACHU:
        name = "Pikachu";
        attack_interval = 400;
        break;

    case HITOKAGE:
        name = "Hitokage";
        power = 40;
        break;

    case ZENIGAME:
        name = "Zenigame";
        power = 40;
        break;

    case FUSHIGIDANE:
        name = "Fushigidane";
        hp = 350;
        break;

    case DEWGONG:
        name = "Dewgong";
        hp = 350;
        break;

    case PERORINGA:
        name = "Peroringa";
        defence = 40;
        break;
    }
}

void my_pokemon::print()
{
    qDebug() << "user_id:" << user_id;
    qDebug() << "id:" <<  id << endl;
    qDebug() << "name:" <<  name << endl;
    qDebug() << "level:" <<  level << endl;
    qDebug() << "exp:" << exp << endl;
    qDebug() << "hp:" << hp << endl;
    qDebug() << "power:" <<  power << endl;
    qDebug() << "defence:" <<  defence << endl;
    qDebug() << "attack_interval:" <<  attack_interval << endl;
}

