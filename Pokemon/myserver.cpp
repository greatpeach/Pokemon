#include "myserver.h"
#include <Windows.h>

myserver::myserver()
{
    mySendingSocket = new QUdpSocket;
    myReceivingSocket = new QUdpSocket;
    while(!mySendingSocket->bind(send_port,QUdpSocket::DontShareAddress)|| \
          !myReceivingSocket->bind(rece_port,QUdpSocket::DontShareAddress))
    {
        send_port += 2;
        rece_port += 2;
    }
    connect(this->myReceivingSocket,SIGNAL(readyRead()),this,SLOT(receive_data()));
    get_server_address();
}

//获取服务器ip
void myserver::get_server_address()
{
    qDebug("get server ip");
    QByteArray msg = QByteArray::number(GET_SERVER_IP);
    mySendingSocket->writeDatagram(msg.data(), sizeof(msg), QHostAddress::Broadcast, dest_port);
}

//发送数据报
void myserver::send_data(QByteArray msg)
{
    qDebug() << "send datagram:" << msg;
    mySendingSocket->writeDatagram(msg.data(), server_ip, dest_port);
}

//接受数据报
void myserver::receive_data()
{
    while(myReceivingSocket->hasPendingDatagrams())
    {
        qDebug("data received");

        QHostAddress server_ip;
        QByteArray msg;
        msg.resize(myReceivingSocket->pendingDatagramSize());
        myReceivingSocket->readDatagram(msg.data(), msg.size(), &server_ip);
        qDebug()<<"receive data: "<<msg;
        QList<QByteArray> list = msg.split(';');

        int manipulate = list[0].toInt();
        int status;
        QPair<QString,int> temp;
        QVector<QPair<QString,int>> user_list;
        int pkm_num;
        QList<int> choice;
        qDebug()<<manipulate;

        switch(manipulate)
        {
        case GET_SERVER_IP:
            this->server_ip = server_ip;
            qDebug()<<this->server_ip;
            break;

        case LOGIN:
            status = list[1].toInt();
            switch(status)
            {
            case LOGIN_SUCCESSFUL:
                emit game_login(this->user_id);
                break;

            case LOGIN_NO_USER:
                emit draw_warning("User Doesn't Exist");
                break;

            case LOGIN_WRONG_PASSWORD:
                emit draw_warning("Wrong Password");
                break;
            }
            break;

        case REGISTER:
            status = list[1].toInt();
            switch(status)
            {
            case REGIST_SUCCESSFUL:
                emit game_login(this->user_id);
                emit init_pkm();
                choice = init_pokemon();
                for(int j=0;j<3;j++)
                {
                    my_pkm_container tmp;//无用临时变量
                    update_pkm(NEW_PKM, choice[j], tmp);
                }
                break;

            case REGIST_EXIST:
                emit draw_warning("User Already Exists");
                break;

            case REGIST_FAILED:
                emit draw_warning(("Register Failed"));
                break;
            }
            break;

        case GET_USERS:
            list.pop_front();
            refresh_user_list(list);
            break;

        case GET_POKEMONLIST:
            if(!list[1].toInt())
            {
                emit draw_warning("This User has no Pokemon");
            }
            else
            {
                list.pop_front();//弹出manipulate
                pkm_num = list[0].toInt();
                list.pop_front();//弹出精灵个数
                send_pokemonlist(list, pkm_num);
            }
            break;

        case REFRESH_MY_POKEMON:
            list.pop_front();//弹出manipulate
            refresh_my_pokemon(list);
            break;

        case INIT_MY_USER:
            list.pop_front();
            refresh_my_user(list);
            break;

        case GET_SERVER_PKM:
            list.pop_front();
            get_server_pkm(list);
            break;
        }
    }
    Sleep(500);

}

//发送登录请求
void myserver::login(QString user_id, QString user_password)
{
    this->user_id = user_id;
    this->user_password = user_password;
    QByteArray msg = QByteArray::number(LOGIN);
    msg += ";" + user_id;
    msg += ";" + user_password;
    send_data(msg);
}

//发送注册请求
void myserver::regist(QString regist_id, QString regist_password)
{
    this->user_id = regist_id;
    this->user_password = regist_password;
    QByteArray msg = QByteArray::number(REGISTER);
    msg += ";" + regist_id;
    msg += ";" + regist_password;
    send_data(msg);
}

//获取所有用户信息
void myserver::get_users()
{
    QByteArray msg;
    msg = QByteArray::number(GET_USERS);
    send_data(msg);
}

//获取某一用户的详细精灵信息
void myserver::get_pokemonlist(QString user_id)
{
    qDebug("get_pokemonlist");
    QByteArray msg;
    msg = QByteArray::number(GET_POKEMONLIST);
    msg += ";" + user_id;
    send_data(msg);
}

//发送下线信息
void myserver::exit()
{
    QByteArray msg;
    msg = QByteArray::number(EXIT);
    msg += ";" + user_id;
    qDebug()<<user_id;
    send_data(msg);
}

//收取某一用户的所有精灵信息
void myserver::send_pokemonlist(QList<QByteArray> list, int pkm_num)
{
    qDebug()<<list;
    static int pkm_count = 0;
    pkm_count++;
    int num = list[0].toInt();
    int id = list[1].toInt();
    QString name = list[2];
    int level = list[3].toInt();
    int exp = list[4].toInt();
    int hp = list[5].toInt();
    int power = list[6].toInt();
    int defence = list[7].toInt();
    int attack_interval = list[8].toInt();
    my_pkm_container pokemon(num, id, name, level, exp, hp, power, defence, attack_interval);
    pkm_buffer.append(pokemon);
    if(pkm_num==pkm_count)
    {
        emit send_pokemon(pkm_buffer);
        pkm_buffer.clear();
        pkm_count = 0;
    }
}

//向服务器增加、更新、删除精灵
void myserver::update_pkm(int manipulate, int id, my_pkm_container pkm)//id表示新添加的精灵的id
{
    QByteArray msg = QByteArray::number(UPDATE_PKM);
    switch(manipulate)
    {
    case NEW_PKM:
        msg += ";" + QByteArray::number(NEW_PKM);
        msg += ";" + QByteArray::number(id);
        msg += ";" + user_id;
        break;

    case CHANGE_PKM:
        msg += ";" + QByteArray::number(CHANGE_PKM);
        pkm.print();
        msg += ";" + pkm.toByteArray();
        msg += ";" + user_id;
        break;

    case DELETE_PKM:
        msg += ";" + QByteArray::number(DELETE_PKM);
        msg += ";" + QByteArray::number(pkm.num);
        msg += ";" + user_id;
    }
    send_data(msg);
}

//获得三只初始精灵
QList<int> myserver::init_pokemon()
{
    int pkm[3] = {0, 0, 0};
    pkm[0] = rand() % 6 + 1;
    int temp;
    while(!(pkm[1]&&pkm[2]))
    {
        temp = rand() % 6 + 1;
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
    qDebug()<<list;
    return list;
}

//更新自己的精灵信息
void myserver::refresh_my_pokemon(QList<QByteArray> list)
{
    my_pokemon *temp;
    int num = list[0].toInt();
    int id = list[1].toInt();
    QString name = list[2];
    int level = list[3].toInt();
    int exp = list[4].toInt();
    int hp = list[5].toInt();
    int power = list[6].toInt();
    int defence = list[7].toInt();
    int attack_interval = list[8].toInt();
    switch(id)
    {
    case PIKACHU:
        temp = new my_Pikachu(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;

    case HITOKAGE:
        temp = new my_Hitokage(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;

    case ZENIGAME:
        temp = new my_Zenigame(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;

    case FUSHIGIDANE:
        temp = new my_Fushigidane(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;

    case DEWGONG:
        temp = new my_Dewgong(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;

    case PERORINGA:
        temp = new my_Peroringa(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;
    }
    emit refresh_pokemon(temp);
}

//更新服务器用户数据
void myserver::update_user_info(myuser user)
{
    QByteArray msg;
    msg = QByteArray::number(UPDATE_USER_INFO);
    msg += ";" + user.user_id;
    msg += ";" + QByteArray::number(user.win_count);
    msg += ";" + QByteArray::number(user.total_count);
    msg += ";" + QByteArray::number(user.senior_pkm_medal);
    msg += ";" + QByteArray::number(user.number_pkm_medal);
    msg += ";" + QByteArray::number(user.wincount_medal);
    msg += ";" + QByteArray::number(user.primary_medicine);
    msg += ";" + QByteArray::number(user.junior_medicine);
    msg += ";" + QByteArray::number(user.senior_medicine);
    msg += ";" + QByteArray::number(user.status_medicine);
    msg += ";" + QByteArray::number(user.money);
    send_data(msg);
}

//获取用户信息
void myserver::init_my_user()
{
    QByteArray msg;
    msg = QByteArray::number(INIT_MY_USER);
    msg += ";" + user_id;
    send_data(msg);
}

//初始化用户信息
void myserver::refresh_my_user(QList<QByteArray> list)
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
    emit init_user(user);
}

//获得用户列表
void myserver::refresh_user_list(QList<QByteArray> msg)
{
    QVector<myuser> user_list;
    QVector<int> online_status;
    while(msg.size())
    {
        myuser temp;
        temp.user_id = msg[0];
        msg.pop_front();
        temp.win_count = msg[0].toInt();
        msg.pop_front();
        temp.total_count = msg[0].toInt();
        msg.pop_front();
        temp.senior_pkm_medal = msg[0].toInt();
        msg.pop_front();
        temp.number_pkm_medal = msg[0].toInt();
        msg.pop_front();
        temp.wincount_medal = msg[0].toInt();
        msg.pop_front();
        user_list.append(temp);

        online_status.append(msg[0].toInt());
        msg.pop_front();
    }
    emit send_user_list(user_list, online_status);
}

void myserver::init_server_pkm()
{
    QByteArray msg;
    msg = QByteArray::number(GET_SERVER_PKM);
    send_data(msg);
}

//获得服务器精灵
void myserver::get_server_pkm(QList<QByteArray> list)
{
    my_pokemon *temp;
    int num = list[0].toInt();
    int id = list[1].toInt();
    QString name = list[2];
    int level = list[3].toInt();
    int exp = list[4].toInt();
    int hp = list[5].toInt();
    int power = list[6].toInt();
    int defence = list[7].toInt();
    int attack_interval = list[8].toInt();
    switch(id)
    {
    case PIKACHU:
        temp = new my_Pikachu(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;

    case HITOKAGE:
        temp = new my_Hitokage(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;

    case ZENIGAME:
        temp = new my_Zenigame(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;

    case FUSHIGIDANE:
        temp = new my_Fushigidane(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;

    case DEWGONG:
        temp = new my_Dewgong(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;

    case PERORINGA:
        temp = new my_Peroringa(num, id, name, level, exp, hp, power, defence, attack_interval);
        break;
    }
    emit send_server_pkm(temp);
}

