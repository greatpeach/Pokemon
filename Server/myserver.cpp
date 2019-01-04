#include "myserver.h"
#include <Windows.h>

myserver::myserver()
{
    //初始化udp端口
    mySendingSocket = new QUdpSocket;
    myReceivingSocket = new QUdpSocket;
    mySendingSocket->bind(send_port,QUdpSocket::DontShareAddress);
    myReceivingSocket->bind(rece_port,QUdpSocket::DontShareAddress);
    connect(this->myReceivingSocket, SIGNAL(readyRead()), this, SLOT(receive_data()));
    qDebug("server runing");
    qDebug()<<"listening on"<<rece_port;

    //初始化数据库
    mydatabase_ = new mydatabase;

    my_pokemon temp;
    temp.num = 1;
    temp.id = 1;
    temp.name = "皮卡丘";
    temp.level = 15;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "server";
    mydatabase_->insertPokemon(temp);

    temp.num = 2;
    temp.id = 2;
    temp.name = "小火龙";
    temp.level = 13;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "server";
    mydatabase_->insertPokemon(temp);

    temp.num = 3;
    temp.id = 3;
    temp.name = "杰尼龟";
    temp.level = 10;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "server";
    mydatabase_->insertPokemon(temp);

    temp.num = 4;
    temp.id = 4;
    temp.name = "妙蛙种子";
    temp.level = 7;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "server";
    mydatabase_->insertPokemon(temp);

    temp.num = 14;
    temp.id = 5;
    temp.name = "白海狮";
    temp.level = 5;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "server";
    mydatabase_->insertPokemon(temp);

    temp.num = 15;
    temp.id = 6;
    temp.name = "大舌头";
    temp.level = 3;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "server";
    mydatabase_->insertPokemon(temp);

    temp.num = 16;
    temp.id = 1;
    temp.name = "皮卡丘";
    temp.level = 1;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "server";
    mydatabase_->insertPokemon(temp);


    temp.num = 5;
    temp.id = 1;
    temp.name = "皮卡丘";
    temp.level = 15;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "presentation";
    mydatabase_->insertPokemon(temp);

    temp.num = 6;
    temp.id = 2;
    temp.name = "小火龙";
    temp.level = 15;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "presentation";
    mydatabase_->insertPokemon(temp);

    temp.num = 7;
    temp.id = 3;
    temp.name = "杰尼龟";
    temp.level = 15;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "presentation";
    mydatabase_->insertPokemon(temp);

    temp.num = 8;
    temp.id = 4;
    temp.name = "妙蛙种子";
    temp.level = 15;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "presentation";
    mydatabase_->insertPokemon(temp);

    temp.num = 9;
    temp.id = 5;
    temp.name = "白海狮";
    temp.level = 14;
    temp.exp = temp.level*temp.level*temp.level-1;
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "presentation";
    mydatabase_->insertPokemon(temp);

    temp.num = 10;
    temp.id = 6;
    temp.name = "大舌头";
    temp.level = 1;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "presentation";
    mydatabase_->insertPokemon(temp);

    temp.num = 11;
    temp.id = 6;
    temp.name = "大舌头";
    temp.level = 1;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "presentation";
    mydatabase_->insertPokemon(temp);

    temp.num = 12;
    temp.id = 6;
    temp.name = "大舌头";
    temp.level = 1;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "presentation";
    mydatabase_->insertPokemon(temp);

    temp.num = 13;
    temp.id = 6;
    temp.name = "大舌头";
    temp.level = 1;
    temp.exp = (temp.level-1)*(temp.level-1)*(temp.level-1);
    temp.hp = 300 + 10*temp.level;
    temp.power = 30 + 3*temp.level;
    temp.defence = 30 + 3*temp.level;
    temp.attack_interval = 500 - 2*temp.level;
    temp.user_id = "presentation";
    mydatabase_->insertPokemon(temp);


    pkm_count = mydatabase_->get_pkm_num();//初始化最大num

    myuser tmp;
    tmp.status_medicine = 0;
    tmp.money = 2000;
    tmp.junior_medicine = 0;
    tmp.senior_medicine = 0;
    tmp.primary_medicine = 0;
    tmp.number_pkm_medal = 0;
    tmp.win_count = 0;
    tmp.senior_pkm_medal = 0;
    tmp.win_count = 14;
    tmp.total_count = 20;
    tmp.user_id = "presentation";
    tmp.user_password = "b";
    mydatabase_->insertUser(tmp);



//    mydatabase_->printPkmTable();
//    mydatabase_->printUserTable();

}

//发送报文
void myserver::send_data(QByteArray msg, QHostAddress sender_ip, quint16 sender_port)
{
    qDebug()<<"data sent:" << msg;
    mySendingSocket->writeDatagram(msg, sender_ip, sender_port);
}

//发送空报文以提供服务器ip
void myserver::send_ip(QHostAddress sender_ip, quint16 sender_port)
{
    QByteArray msg;
    msg = QString::number(GET_SERVER_IP).toUtf8();
    send_data(msg, sender_ip, sender_port);
}

//处理用户登录
bool myserver::login(QString user_id, QString user_password, QHostAddress sender_ip, quint16 sender_port)
{
    bool ok = false;
    QVector<QByteArray> user;
    QByteArray msg;
    msg = QString::number(LOGIN).toUtf8();
    msg += ";";
    if(mydatabase_->getUser(user_id, user))
    {
        qDebug()<<user;
        //用户存在
        if(user.at(1) == user_password)
        {
            //密码正确
            refresh_online_user(user_id, ONLINE);//更新在线用户
            msg += QString::number(LOGIN_SUCCESSFUL);
            ok = true;
        }
        else
        {
            //密码不正确
            msg += QString::number(LOGIN_WRONG_PASSWORD);
        }
    }
    else
    {
        //用户不存在
        msg += QString::number(LOGIN_NO_USER);
    }
    send_data(msg, sender_ip, sender_port);
    return ok;
}

//处理用户注册
void myserver::regist(QString user_id, QString user_password, QHostAddress sender_ip, quint16 sender_port)
{
    myuser user;
    QVector<QByteArray> temp;
    QByteArray msg;
    msg = QByteArray::number(REGISTER);
    msg += ";";
    if(mydatabase_->getUser(user_id, temp))
    {
        //用户已存在
        msg += QByteArray::number(REGIST_EXIST);
    }
    else
    {
        user.user_id = user_id;
        user.user_password = user_password;
        user.money = 2000;//金币数量初始化为2000
        if(mydatabase_->insertUser(user))
        {
            //插入用户成功
            refresh_online_user(user_id, ONLINE);//更新在线用户
            msg += QByteArray::number(REGIST_SUCCESSFUL);
        }
        else//插入用户失败
            msg += QByteArray::number(REGIST_FAILED);
    }
    send_data(msg, sender_ip, sender_port);
}

//更新在线用户列表
void myserver::refresh_online_user(QString user_id, int status)
{
    if(status==ONLINE)
    {
        if(online_user.count(user_id)==0)
            online_user.append(user_id);
    }
    else
    {
        online_user.removeOne(user_id);
    }
}

//发送所有用户信息
void myserver::send_userlist(QVector<QVector<QString>> user_list, QHostAddress sender_ip, quint16 sender_port)
{
    QByteArray msg = QByteArray::number(GET_USERS);
    for(int i=0;i < user_list.size();i++)
    {
        msg += ";" + user_list[i][0];
        for(int j=1;j<6;j++)
            msg += ";" + user_list[i][j];
        if(online_user.count(user_list[i][0]))
            msg += ";" + QByteArray::number(ONLINE);
        else
            msg += ";" + QByteArray::number(OFFLINE);
    }
    send_data(msg, sender_ip, sender_port);
}

//发送某用户的精灵信息
void myserver::send_pokemonlist(QVector<QVector<QString>> pokemon_list, QHostAddress sender_ip, quint16 sender_port)
{
    if(pokemon_list.size())
        for(int j=0;j<pokemon_list.size();j++)
        {
            QByteArray msg;
            msg = QByteArray::number(GET_POKEMONLIST);
            msg += ";" + QByteArray::number(pokemon_list.size());
            for(int i=0;i<pokemon_list.at(j).size();i++)
            {
                msg += ";" + pokemon_list.at(j).at(i);
            }
            send_data(msg, sender_ip, sender_port);
        }
    else
    {
        QByteArray msg;
        msg = QByteArray::number(GET_POKEMONLIST);
        msg += ";" + QByteArray::number(0);
        send_data(msg, sender_ip, sender_port);
    }

}

//为用户增加精灵
void myserver::new_pkm(QList<QByteArray> list, QHostAddress sender_ip, quint16 sender_port)
{
    //插入精灵
    int id = list[0].toInt();
    QString user_id = list[1];
    my_pokemon pkm(id, ++pkm_count, user_id);//根据精灵id生成一只1级的对应精灵
    mydatabase_->insertPokemon(pkm);
    //返回精灵
    QByteArray msg = QByteArray::number(REFRESH_MY_POKEMON);
    msg += ";" + QByteArray::number(pkm.num);
    msg += ";" + QByteArray::number(pkm.id);
    msg += ";" + pkm.name;
    msg += ";" + QByteArray::number(pkm.level);
    msg += ";" + QByteArray::number(pkm.exp);
    msg += ";" + QByteArray::number(pkm.hp);
    msg += ";" + QByteArray::number(pkm.power);
    msg += ";" + QByteArray::number(pkm.defence);
    msg += ";" + QByteArray::number(pkm.attack_interval);
    send_data(msg, sender_ip, sender_port);
}

//为用户更新精灵信息
void myserver::change_pkm(QList<QByteArray> list)
{
    my_pokemon temp;
    temp.num = list[0].toInt();
    temp.id = list[1].toInt();
    temp.name = list[2];
    temp.level = list[3].toInt();
    temp.exp = list[4].toInt();
    temp.hp = list[5].toInt();
    temp.power = list[6].toInt();
    temp.defence = list[7].toInt();
    temp.attack_interval = list[8].toInt();
    temp.user_id = list[9];
    mydatabase_->updatePokemon(temp);
}

//为用户删除精灵
void myserver::delete_pkm(QList<QByteArray> list)
{
    int num = list[0].toInt();
    mydatabase_->deletePokemon(num);
}

//发送用户自己的精灵信息
void myserver::send_my_pokemon(QVector<QVector<QString>> pokemon_list, QHostAddress sender_ip, quint16 sender_port)
{

    for(int j=0;j<pokemon_list.size();j++)
    {
        QByteArray msg;
        msg = QString::number(REFRESH_MY_POKEMON).toUtf8();
        for(int i=0;i<pokemon_list.at(j).size();i++)
        {
            msg += ";" + pokemon_list.at(j).at(i);
        }
        send_data(msg, sender_ip, sender_port);
    }
}

//更新用户信息
void myserver::update_user_info(QList<QByteArray> list)
{
    myuser user;
    user.user_id = list[0];
    user.win_count = list[1].toInt();
    user.total_count = list[2].toInt();
    user.senior_pkm_medal = list[3].toInt();
    user.number_pkm_medal = list[4].toInt();
    user.wincount_medal = list[5].toInt();
    user.primary_medicine = list[6].toInt();
    user.junior_medicine = list[7].toInt();
    user.senior_medicine = list[8].toInt();
    user.status_medicine = list[9].toInt();
    user.money = list[10].toInt();
    mydatabase_->updateUser(user);
}

//初始化用户信息
void myserver::init_my_user(QByteArray user_id, QHostAddress sender_ip, quint16 sender_port)
{
    QVector<QByteArray> user;
    QByteArray msg;
    msg = QByteArray::number(INIT_MY_USER);
    msg += ";" + user_id;
    mydatabase_->getUser(user_id, user);
    for(int i=2;i<user.size();i++)
    {
       msg += ";" + user.at(i);
    }
    send_data(msg, sender_ip, sender_port);
}

//获取服务器精灵
void myserver::init_server_pkm(QVector<QVector<QString>> pokemon_list, QHostAddress sender_ip, quint16 sender_port)
{
    for(int j=0;j<pokemon_list.size();j++)
    {
        QByteArray msg;
        msg = QByteArray::number(GET_SERVER_PKM);
        for(int i=0;i<pokemon_list.at(j).size();i++)
        {
            msg += ";" + pokemon_list.at(j).at(i);
        }
        send_data(msg, sender_ip, sender_port);
    }
}

//接受数据报
void myserver::receive_data()
{
    while(myReceivingSocket->hasPendingDatagrams())
    {
        qDebug("data received");
        QHostAddress sender_ip;
        quint16 sender_port;
        QByteArray msg;
        msg.resize(myReceivingSocket->pendingDatagramSize());
        myReceivingSocket->readDatagram(msg.data(), msg.size(), &sender_ip, &sender_port);
        qDebug()<<msg;
        QList<QByteArray> list = msg.split(';');
        int manipulate = list[0].toInt();
        list.pop_front();
        QString user_id, user_password;

        switch (manipulate)
        {
        case GET_SERVER_IP:
            qDebug()<<"Get IP";
            send_ip(sender_ip, sender_port+1);
            break;

        case LOGIN:
            user_id = list[0];
            user_password = list[1];
            qDebug()<<"Login,"<<user_id<<","<<user_password;
            if(login(user_id, user_password, sender_ip, sender_port+1))
                send_my_pokemon(mydatabase_->get_pokemonlist(user_id), sender_ip, sender_port+1);
            break;

        case REGISTER:
            user_id = list[0];
            user_password = list[1];
            qDebug()<<"Register,"<<user_id<<","<<user_password;
            regist(user_id, user_password, sender_ip, sender_port+1);
            break;

        case GET_USERS:
            qDebug()<<"Get users";
            send_userlist(mydatabase_->get_userlist(), sender_ip, sender_port+1);
            break;

        case GET_POKEMONLIST:
            qDebug()<<"Get Pokemon list";
            user_id = list[0];
            send_pokemonlist(mydatabase_->get_pokemonlist(user_id), sender_ip, sender_port+1);
            break;

        case EXIT:
            qDebug()<<"Exit";
            user_id = list[0];
            refresh_online_user(user_id, OFFLINE);
            break;

        case UPDATE_PKM:
            qDebug()<<"Update pokemon";
            switch(list[0].toInt())
            {
            case NEW_PKM:
                list.pop_front();
                new_pkm(list, sender_ip, sender_port+1);
                break;

            case CHANGE_PKM:
                list.pop_front();
                change_pkm(list);
                break;

            case DELETE_PKM:
                list.pop_front();
                delete_pkm(list);
                break;
            }
            break;

        case UPDATE_USER_INFO:
            qDebug()<<"Update user info";
            update_user_info(list);
            break;

        case INIT_MY_USER:
            qDebug()<<"Init my user";
            init_my_user(list[0], sender_ip, sender_port+1);
            break;

        case GET_SERVER_PKM:
            qDebug()<<"Get server pkm";
            init_server_pkm(mydatabase_->get_pokemonlist("server"), sender_ip, sender_port+1);
            break;
        }
    }
}


