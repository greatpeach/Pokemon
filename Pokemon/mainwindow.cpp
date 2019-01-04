#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    login_window = new login_widget;
    login_window->show();

    myserver_ = new myserver;
    user = new myuser;
    connect(myserver_,SIGNAL(draw_warning(QString)),login_window,SLOT(draw_warning(QString)));
    connect(login_window,SIGNAL(send_login(QString,QString)),myserver_,SLOT(login(QString,QString)));
    connect(login_window,SIGNAL(send_regist(QString,QString)),myserver_,SLOT(regist(QString,QString)));
    connect(myserver_,SIGNAL(game_login(QString)),this,SLOT(start(QString)));
    connect(myserver_,SIGNAL(init_pkm()),this,SLOT(init_pkm()));
    connect(myserver_,SIGNAL(refresh_pokemon(my_pokemon*)),this,SLOT(refresh_pokemon(my_pokemon*)));
    connect(myserver_,SIGNAL(init_user(myuser)),this,SLOT(init_user(myuser)));
    connect(myserver_,SIGNAL(send_server_pkm(my_pokemon*)),this,SLOT(refresh_server_pkm(my_pokemon*)));
    connect(this->user,SIGNAL(draw_information(QString)),this,SLOT(draw_information(QString)));
    ui->setupUi(this);

    user_list_ = new user_list(this);
    user_list_->setGeometry(geometry().width()-500,ui->mainToolBar->geometry().height(),500,this->height()-ui->mainToolBar->height());
    connect(myserver_,SIGNAL(send_user_list(QVector<myuser>, QVector<int>)),user_list_,SLOT(refresh_user(QVector<myuser>, QVector<int>)));
    connect(user_list_,SIGNAL(get_pokemonlist(QString)),myserver_,SLOT(get_pokemonlist(QString)));
    connect(myserver_,SIGNAL(send_pokemon(QList<my_pkm_container>)),this,SLOT(show_pokemon(QList<my_pkm_container>)));

    backpack = new mybackpack();
    backpack->setGeometry(800,300,300,200);

    mypokemoncenter = new pokemon_center_widget();
    connect(mypokemoncenter,SIGNAL(update_user()),this,SLOT(update_user()));
    connect(mypokemoncenter,SIGNAL(recover()),this,SLOT(recover()));

    mybattleground = new battle_ground();
    connect(mybattleground,SIGNAL(update_pkm(int, int, my_pkm_container)),myserver_,SLOT(update_pkm(int, int, my_pkm_container)));//更新精灵//增删改
    connect(mybattleground,SIGNAL(update_user()),this,SLOT(update_user()));//更新用户

    my_bgm = new music_thread;
    connect(this,SIGNAL(stop_music()),my_bgm,SLOT(stop_music()));
    my_bgm->start();


}

MainWindow::~MainWindow()
{
    delete ui;
}

//显示主界面
void MainWindow::start(QString user_id)
{
    login_window->close();
    this->show();
    emit stop_music();
    user->user_id = user_id;
    myserver_->init_my_user();//初始化用户信息
    myserver_->init_server_pkm();//初始化对战列表
}

//退出确认界面
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button=QMessageBox::question(this,tr("exit"),QString(tr("您确定要退出吗?")),QMessageBox::Yes|QMessageBox::No);
    if(button==QMessageBox::No)
    {
        event->ignore(); // 忽略退出信号，程序继续进行
    }
    else if(button==QMessageBox::Yes)
    {
        myserver_->exit();
        event->accept(); // 接受退出信号，程序退出
    }

}

//获取用户列表
void MainWindow::on_show_userlist_triggered(bool checked)
{
    if(checked)
        myserver_->get_users();
    else
        user_list_->hide();
}

//显示其他用户精灵窗口
void MainWindow::show_pokemon(QList<my_pkm_container> pkm)
{
    QTabWidget *pkm_list = new QTabWidget;
    pkm_list->resize(475,500);
    for(int i=0;i<pkm.size();i++)
    {
        pokemon_widget *temp = new pokemon_widget;
        temp->show_pokemon(pkm[i]);
        pkm_list->addTab(temp,pkm[i].name);
    }
    pkm_list->show();
}

//初始精灵提示
void MainWindow::init_pkm()
{
    QMessageBox::information(this, QString::fromUtf8("恭喜"), QString::fromUtf8("您获得了3只新精灵，请在“精灵”中查看"));
    QMessageBox::information(this, QString::fromUtf8("恭喜"), QString::fromUtf8("您获得了2000金币,请在“背包”中查看"));
}

//游戏开始后从服务器获得自己已有的精灵
void MainWindow::refresh_pokemon(my_pokemon *pkm)
{
    pkm_list.append(pkm);
}

//精灵信息更改后向服务器更新
void MainWindow::update_pkm(my_pkm_container pkm)
{
    myserver_->update_pkm(CHANGE_PKM, 0, pkm);
}

//初始化用户信息
void MainWindow::init_user(myuser user)
{
    *this->user = user;
}

void MainWindow::draw_information(QString msg)
{
    QMessageBox::information(this, "恭喜", msg);
}

//向服务器更新用户信息
void MainWindow::update_user()
{
    myserver_->update_user_info(*user);
}

//获得服务器精灵
void MainWindow::refresh_server_pkm(my_pokemon *pkm)
{
    this->server_list.append(pkm);
    pkm->to_pkmcontainer().print();
}

void MainWindow::recover()
{
    for(int i=0;i<pkm_list.size();i++)
    {
        pkm_list[i]->recover();
    }
}

//显示自己的精灵
void MainWindow::on_show_pokemon_triggered()
{
    QTabWidget *pkm_list = new QTabWidget;
    pkm_list->resize(475,500);
    pkm_list->setMinimumSize(475,500);
    pkm_list->setMaximumSize(475,500);
    QList<my_pkm_container> container_list;
    for(int i=0;i<this->pkm_list.size();i++)
    {
        container_list.append(this->pkm_list[i]->to_pkmcontainer());
    }
    for(int i=0;i<container_list.size();i++)
    {
        pokemon_widget *temp = new pokemon_widget;
        temp->show_own_pokemon(container_list[i]);
        pkm_list->addTab(temp,container_list[i].name);
        connect(temp,SIGNAL(pkm_changed(my_pkm_container)),this,SLOT(update_pkm(my_pkm_container)));
    }
    pkm_list->setWindowTitle("我的精灵");
    pkm_list->show();
}

//进入道馆界面
void MainWindow::on_enter_battleground_clicked()
{
    qDebug()<<"enter battleground";
    mybattleground->show_battleground(&pkm_list, &server_list, user);
}

//显示背包
void MainWindow::on_show_backpack_triggered()
{
    backpack->refresh_mybackpack(*user);
}

//进入神奇宝贝中心
void MainWindow::on_enter_pokemon_center_clicked()
{
    mypokemoncenter->refresh_pokemon_center(user);
}
