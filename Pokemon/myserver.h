#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <Windows.h>
#include <mydatagram.h>
#include <QHostInfo>
#include "my_pokemon.h"
#include "myuser.h"

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

#define LOGIN_SUCCESSFUL 0
#define LOGIN_NO_USER 1
#define LOGIN_WRONG_PASSWORD 2

#define REGIST_SUCCESSFUL 0
#define REGIST_EXIST 1
#define REGIST_FAILED 2

#define OFFLINE 0
#define ONLINE 1

#define NEW_PKM 0
#define CHANGE_PKM 1
#define DELETE_PKM 2


class myserver : public QObject
{
    Q_OBJECT

public:
    myserver();
    void send_data(QByteArray);
    void get_server_address();
    QList<my_pkm_container> pkm_buffer;

private:
    QUdpSocket *mySendingSocket;
    QUdpSocket *myReceivingSocket;
    QHostAddress server_ip;
    quint16 send_port = 8090;
    quint16 rece_port = 8091;
    quint16 dest_port = 8081;

    QString user_id;
    QString user_password;

signals:
    void draw_warning(QString);
    void game_login(QString);
    void send_user_list(QVector<myuser>, QVector<int>);
    void send_pokemon(QList<my_pkm_container>);
    void init_pkm();
    void refresh_pokemon(my_pokemon*);
    void init_user(myuser);
    void send_server_pkm(my_pokemon*);

public slots:
    void receive_data();
    void login(QString, QString);
    void regist(QString, QString);
    void get_users();
    void get_pokemonlist(QString);
    void exit();
    void send_pokemonlist(QList<QByteArray>, int);
    void update_pkm(int, int, my_pkm_container);
    QList<int> init_pokemon();
    void refresh_my_pokemon(QList<QByteArray>);
    void update_user_info(myuser);
    void init_my_user();
    void refresh_my_user(QList<QByteArray>);
    void refresh_user_list(QList<QByteArray>);
    void init_server_pkm();
    void get_server_pkm(QList<QByteArray>);
};






#endif // MYSERVER_H
