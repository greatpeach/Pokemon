#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QByteArray>
#include "mydatabase.h"
#include <mydatagram.h>
#include <QHostInfo>
#include <QList>

#define GET_SERVER_IP 0
#define LOGIN 1
#define REGISTER 2
#define GET_USERS 3
#define GET_POKEMONLIST 4
#define EXIT 5
#define UPDATE_PKM 6
#define REFRESH_MY_POKEMON 7
#define UPDATE_USER_INFO 8
#define INIT_MY_USER 9
#define GET_SERVER_PKM 10
#define SEND_NEW_PKM 11

//登录状态
#define LOGIN_SUCCESSFUL 0
#define LOGIN_NO_USER 1
#define LOGIN_WRONG_PASSWORD 2

//注册状态
#define REGIST_SUCCESSFUL 0
#define REGIST_EXIST 1
#define REGIST_FAILED 2

//在线状态
#define OFFLINE 0
#define ONLINE 1

//更新宝可梦
#define NEW_PKM 0
#define CHANGE_PKM 1
#define DELETE_PKM 2

class myserver : public QObject
{
    Q_OBJECT
public:
    myserver();
    ~myserver(){}

private:
    QUdpSocket *mySendingSocket;//发送Socket
    QUdpSocket *myReceivingSocket;//接收Socket
    quint16 send_port = 8080;//发送端口
    quint16 rece_port = 8081;//接受端口
    mydatabase *mydatabase_;//数据库
    QList<QString> online_user;//在线用户列表

    int pkm_count;//精灵num计数

public slots:
    void send_data(QByteArray, QHostAddress, quint16);//发送报文
    void receive_data();//接受报文

    void send_ip(QHostAddress, quint16);//发送服务器ip
    bool login(QString, QString, QHostAddress, quint16);//处理登陆请求
    void regist(QString, QString, QHostAddress, quint16);//处理注册请求
    void refresh_online_user(QString,int);//更新用户列表
    void send_userlist(QVector<QVector<QString>>, QHostAddress, quint16);//发送用户列表
    void send_pokemonlist(QVector<QVector<QString>>, QHostAddress, quint16);//发送用户精灵信息
    void new_pkm(QList<QByteArray>, QHostAddress, quint16);//用户获取新精灵
    void change_pkm(QList<QByteArray>);//更新用户精灵信息
    void delete_pkm(QList<QByteArray>);//删除精灵
    void send_my_pokemon(QVector<QVector<QString>>, QHostAddress, quint16);//发送用户自己的精灵信息
    void update_user_info(QList<QByteArray>);//更新用户信息
    void init_my_user(QByteArray, QHostAddress, quint16);//初始化用户信息
    void init_server_pkm(QVector<QVector<QString>>, QHostAddress, quint16);//初始化服务器精灵列表
};






#endif // MYSERVER_H
