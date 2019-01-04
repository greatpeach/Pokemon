#ifndef BATTLE_GROUND_H
#define BATTLE_GROUND_H

#include <QWidget>
#include "my_pokemon.h"
#include <QStandardItemModel>
#include "myuser.h"
#include "battle_field.h"
#include <QMessageBox>
#include <windows.h>


#define EXP_BATTLE 0
#define PKM_BATTLE 1

#define NEW_PKM 0
#define CHANGE_PKM 1
#define DELETE_PKM 2

namespace Ui {
class battle_ground;
}

class battle_ground : public QWidget
{
    Q_OBJECT

public:
    explicit battle_ground(QWidget *parent = nullptr);
    void show_battleground(QList<my_pokemon*>*, QList<my_pokemon*>*, myuser*);
    ~battle_ground();

private:
    Ui::battle_ground *ui;
    battle_field *mybattlefield;//战斗界面
    QList<my_pokemon*> *pkm_list;//用户精灵列表
    QList<my_pokemon*> *server_list;//服务器精灵列表
    myuser *user;//用户信息
    QStandardItemModel *model1;
    QStandardItemModel *model2;
    my_pokemon* p1;//用户选择的己方精灵
    my_pokemon* p2;//用户选择的对方精灵
    int is_auto = 0;//是否自动战斗

    //获得3个int范围内不相同的随机数
    QList<int> get_random_num(int);


public slots:
    void user_list_clicked(const QModelIndex&);
    void server_list_clicked(const QModelIndex&);
    void start_exp_battle();
    void start_pkm_battle();
    void account(int, int);
    void lv_up(int);//升级
    void set_auto(int);
    void senior_pkm_count();
    void wincount_medal_count();
    void pkm_count();

signals:
    void update_pkm(int,int,my_pkm_container);
    void update_user();
private slots:
    void on_go_back_clicked();
};

#endif // BATTLE_GROUND_H
