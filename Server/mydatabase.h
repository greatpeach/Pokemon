#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QObject>
#include <QtSql>
#include <mydatagram.h>
#include <QHostAddress>
#include "my_pokemon.h"
#include "myuser.h"


class mydatabase : public QObject
{
    Q_OBJECT
public:
    mydatabase();
    void createTable();

    bool insertUser(myuser);//插入用户
    bool getUser(QString user_id, QVector<QByteArray> &);//查询用户
    void updateUser(myuser);//更新用户信息
    QVector<QVector<QString>> get_userlist();//获取用户列表
    QVector<QVector<QString>> get_pokemonlist(QString);//获取某用户的精灵信息
    void printUserTable();//输出用户表（用于调试）

    int get_pkm_num();//更新最大精灵pkm_count
    bool insertPokemon(my_pokemon);//插入精灵
    void updatePokemon(my_pokemon);//更新精灵
    void deletePokemon(int);//删除精灵
    QVector<QString> getPokemon(QString);//查询精灵
    void printPkmTable();//输出精灵表（用于调试）

private:

    QSqlDatabase db;
    QString create_user_tbl = "create table if not exists user  (user_id varchar(30) primary key, "
                              "user_password varchar(30), "
                              "win_count int, "
                              "total_count int, "
                              "senior_pkm_medal int, "
                              "number_pkm_medal int, "
                              "wincount_medal int, "
                              "primary_medicine int, "
                              "junior_medicine int, "
                              "senior_medicine int, "
                              "status_medicine int, "
                              "money int)";
    QString insert_user_tbl = "insert into user values(?,?,?,?,?,?,?,?,?,?,?,?)";
    QString select_all_user_tbl = "select * from user";

    QString create_pkm_tbl = "create table if not exists pkm (num int primary key, "
                             "id int, "
                             "name varchar(30), "
                             "level int, exp int, "
                             "hp int, "
                             "power int, "
                             "defence int, "
                             "attack_interval int, "
                             "user_id varchar(30))";
    QString insert_pkm_tbl = "insert into pkm values(?,?,?,?,?,?,?,?,?,?)";
    QString select_all_pokemon_tbl = "select * from pkm";
};

#endif // MYDATABASE_H
