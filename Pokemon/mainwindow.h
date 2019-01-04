#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QMessageBox>
#include "login_widget.h"
#include "myserver.h"
#include <QCloseEvent>
#include <QString>
#include "user_list.h"
#include <QTabWidget>
#include "pokemon_widget.h"
#include "backpack_widget.h"
#include "pokemon_center_widget.h"
#include "battle_ground.h"
#include "music_thread.h"

#define NEW_PKM 0
#define CHANGE_PKM 1
#define DELETE_PKM 2


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void start(QString);//结束登陆，进入游戏
    void closeEvent(QCloseEvent *event);//关闭窗口的处理
    void on_show_userlist_triggered(bool checked);//打开用户列表界面
    void on_show_pokemon_triggered();//打开精灵界面
    void on_enter_battleground_clicked();//打开道馆界面
    void on_show_backpack_triggered();//打开背包界面
    void on_enter_pokemon_center_clicked();//打开精灵中心界面

public slots:
    void show_pokemon(QList<my_pkm_container>);//显示其他用户的精灵
    void init_pkm();//初始发放精灵
    void refresh_pokemon(my_pokemon*);//从服务器获取自己的精灵信息
    void update_pkm(my_pkm_container);//向服务器更新精灵信息
    void init_user(myuser);//初始化用户信息
    void draw_information(QString);//弹出窗口
    void update_user();//向服务器更新用户信息
    void refresh_server_pkm(my_pokemon*);//获得服务器精灵
    void recover();//恢复精灵状态

private:
    Ui::MainWindow *ui;
    myuser *user;//用户信息
    QList<my_pokemon*> pkm_list;//用户持有的精灵
    QList<my_pokemon*> server_list;//服务器精灵列表
    myserver *myserver_;//网络层
    login_widget *login_window;//登陆界面
    pokemon_center_widget *mypokemoncenter;//精灵中心界面
    user_list *user_list_;//用户列表界面
    mybackpack *backpack;//背包界面
    battle_ground *mybattleground;//道馆界面
    music_thread *my_bgm;//bgm

signals:
    void stop_music();//停止音乐信号
};

#endif // MAINWINDOW_H
