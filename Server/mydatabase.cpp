#include "mydatabase.h"

mydatabase::mydatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db");
    qDebug("database created");
    if(!db.open())
        qDebug()<<"database failed to open";
    createTable();
}

void mydatabase::createTable()
{
    QSqlQuery query;
    query.prepare(create_user_tbl);
    if(!query.exec())
       qDebug()<<"failed to create User table";
    else
        qDebug()<<"User table created";

    query.prepare(create_pkm_tbl);
    if(!query.exec())
        qDebug()<<"failed to create Pokemon table";
    else
        qDebug()<<"Pokemon table created";
}

bool mydatabase::insertUser(myuser user)
{
    QSqlQuery query;
    query.prepare(insert_user_tbl);
    query.bindValue(0,user.user_id);
    query.bindValue(1,user.user_password);
    query.bindValue(2,user.win_count);
    query.bindValue(3,user.total_count);
    query.bindValue(4,user.senior_pkm_medal);
    query.bindValue(5,user.number_pkm_medal);
    query.bindValue(6,user.wincount_medal);
    query.bindValue(7,user.primary_medicine);
    query.bindValue(8,user.junior_medicine);
    query.bindValue(9,user.senior_medicine);
    query.bindValue(10,user.status_medicine);
    query.bindValue(11,user.money);
    user.print();
    if(!query.exec())
    {
        qDebug("failed to insert user");
        return false;
    }
    else
    {
        qDebug()<<"inserted user successfully";
        return true;
    }
}

void mydatabase::updateUser(myuser user)
{
    qDebug()<<"updateuser";
    qDebug()<<user.primary_medicine;
    QSqlQuery query;
    query.prepare("update user set win_count = :win_count ,\
                                   total_count = :total_count ,\
                                   senior_pkm_medal = :senior_pkm_medal ,\
                                   number_pkm_medal = :number_pkm_medal ,\
                                   wincount_medal = :wincount_medal ,\
                                   primary_medicine = :primary_medicine ,\
                                   junior_medicine = :junior_medicine ,\
                                   senior_medicine = :senior_medicine ,\
                                   status_medicine = :status_medicine ,\
                                   money = :money \
                                   where user_id = :user_id");
    query.bindValue(":win_count",user.win_count);
    query.bindValue(":total_count",user.total_count);
    query.bindValue(":senior_pkm_medal",user.senior_pkm_medal);
    query.bindValue(":number_pkm_medal",user.number_pkm_medal);
    query.bindValue(":wincount_medal",user.wincount_medal);
    query.bindValue(":primary_medicine",user.primary_medicine);
    query.bindValue(":junior_medicine",user.junior_medicine);
    query.bindValue(":senior_medicine",user.senior_medicine);
    query.bindValue(":status_medicine",user.status_medicine);
    query.bindValue(":money",user.money);
    query.bindValue(":user_id",user.user_id);
    if(query.exec())
        qDebug("update user successfully");
    else
        qDebug("update user failed");
}

bool mydatabase::getUser(QString user_id, QVector<QByteArray> &user)
{
    QSqlQuery query;
    query.prepare("select * from user where user_id=:user_id");
    query.bindValue(":user_id", user_id);
    query.exec();
    user.append(user_id.toUtf8());
    if(query.next())
    {
        for(int i=1;i<12;i++)
            user.append(query.record().value(i).toByteArray());
        return true;
    }
    else
        return false;
}

void mydatabase::printUserTable()
{
    QSqlQuery query;
    query.prepare(select_all_user_tbl);
    if(query.exec())
    {
        while(query.next())
        {
            for(int i=0;i<2;i++)
                qDebug()<<query.record().fieldName(i)<<query.record().value(i);
        }
    }
    else
        qDebug("error");
}

bool mydatabase::insertPokemon(my_pokemon pkm)
{
    QSqlQuery query;
    query.prepare(insert_pkm_tbl);
    query.bindValue(0,pkm.num);
    query.bindValue(1,pkm.id);
    query.bindValue(2,pkm.name);
    query.bindValue(3,pkm.level);
    query.bindValue(4,pkm.exp);
    query.bindValue(5,pkm.hp);
    query.bindValue(6,pkm.power);
    query.bindValue(7,pkm.defence);
    query.bindValue(8,pkm.attack_interval);
    query.bindValue(9,pkm.user_id);
    if(!query.exec())
    {
        qDebug("failed to insert pokemon");
        return false;
    }
    else
    {
        qDebug()<<"inserted pokemon successfully";
        return true;
    }
}

void mydatabase::updatePokemon(my_pokemon pkm)
{
    QSqlQuery query;
    query.prepare("update pkm set name = :name ,\
                                  id = :id ,\
                                  level = :level ,\
                                  exp = :exp ,\
                                  hp = :hp ,\
                                  power = :power ,\
                                  defence = :defence ,\
                                  attack_interval = :attack_interval \
                                  where num = :num");

    query.bindValue(":name", pkm.name);
    query.bindValue(":id",pkm.id);
    query.bindValue(":level", pkm.level);
    query.bindValue(":exp", pkm.exp);
    query.bindValue(":hp", pkm.hp);
    query.bindValue(":power", pkm.power);
    query.bindValue(":defence", pkm.defence);
    query.bindValue(":attack_interval", pkm.attack_interval);
    query.bindValue(":num", pkm.num);
    query.exec();
}

void mydatabase::deletePokemon(int num)
{
    QSqlQuery query;
    query.prepare("delete from pkm where num =:num");
    query.bindValue(":num",num);
    if(query.exec())
        qDebug()<<"delete"<<num<<"successful";
    else
        qDebug()<<"failed to delete";
}

int mydatabase::get_pkm_num()
{
    QSqlQuery query;
    query.prepare("select num from pkm");
    query.exec();
    int max = 0;
    while(query.next())
    {
        if(max < query.record().value(0).toInt())
            max = query.record().value(0).toInt();
    }
    return max;
}

void mydatabase::printPkmTable()
{
    QSqlQuery query;
    query.prepare("select * from pkm");
    if(query.exec())
        while(query.next())
        {
            for(int i=0;i<10;i++)
                qDebug()<<query.record().fieldName(i)<<query.record().value(i);
            qDebug("\n");
        }
    else
        qDebug("error");
}

QVector<QVector<QString>> mydatabase::get_userlist()
{
    QSqlQuery query;
    QVector<QVector<QString>> user_list;
    query.prepare("select * from user");
    if(query.exec())
    {
        while(query.next())
        {
            QVector<QString> temp;
            temp.append(query.record().value(0).toString());//id
            temp.append(query.record().value(2).toString());//wincount
            temp.append(query.record().value(3).toString());//total
            temp.append(query.record().value(4).toString());//senior
            temp.append(query.record().value(5).toString());//number
            temp.append(query.record().value(6).toString());//win
            user_list.append(temp);
        }
    }
    return user_list;
}

QVector<QVector<QString>> mydatabase::get_pokemonlist(QString user_id)
{
    QSqlQuery query;
    QVector<QVector<QString>> pokemon_list;
    query.prepare("select * from pkm where user_id =:user_id");
    query.bindValue(":user_id",user_id);
    query.exec();
    while(query.next())
    {
        QVector<QString> pokemon;
        for(int i=0;i<9;i++)
        {
            pokemon.append(query.record().value(i).toString());
        }
        pokemon_list.append(pokemon);
    }
    qDebug()<<pokemon_list;
    return pokemon_list;
}
