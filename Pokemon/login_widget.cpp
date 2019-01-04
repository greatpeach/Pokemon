#include "login_widget.h"
#include "ui_login_widget.h"

login_widget::login_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_widget)
{
    ui->setupUi(this);
    ui->user_login->hide();
    ui->user_register->hide();
    ui->back_button->hide();
}

login_widget::~login_widget()
{
    delete ui;
}

//显示登陆窗口
void login_widget::on_login_button_clicked()
{
    ui->main_widget->hide();
    ui->user_login->show();
    ui->back_button->show();
}

//显示注册窗口
void login_widget::on_register_button_clicked()
{
    ui->main_widget->hide();
    ui->user_register->show();
    ui->back_button->show();
}

//退出
void login_widget::on_exit_button_clicked()
{
    this->close();
}

//提交登陆信息
void login_widget::on_submit_login_clicked()
{
    emit send_login(ui->user_id->text(),ui->user_password->text());
}

//提交注册信息
void login_widget::on_submit_register_clicked()
{
    if(ui->register_password->text()==ui->confirm_password->text())
    {
        emit send_regist(ui->register_id->text(),ui->register_password->text());
    }
    else
    {
        ui->register_password->clear();
        ui->confirm_password->clear();
        draw_warning("Password Doesn't Correspond");
    }
}

//错误弹窗
void login_widget::draw_warning(QString warn)
{
    QMessageBox::warning(this->ui->main_widget, "Error", warn);
}

//返回
void login_widget::on_back_button_clicked()
{
    ui->back_button->hide();
    ui->user_login->hide();
    ui->user_register->hide();
    ui->main_widget->show();

    ui->user_id->clear();
    ui->user_password->clear();

    ui->register_id->clear();
    ui->register_password->clear();
    ui->confirm_password->clear();
}


void login_widget::on_user_password_returnPressed()
{
    on_submit_login_clicked();
}

void login_widget::on_confirm_password_returnPressed()
{
    on_submit_register_clicked();
}
