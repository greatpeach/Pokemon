#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMessageBox>

namespace Ui {
class login_widget;
}

class login_widget : public QWidget
{
    Q_OBJECT

public:
    explicit login_widget(QWidget *parent = nullptr);
    ~login_widget();

private:
    Ui::login_widget *ui;

signals:
    void send_login(QString,QString);
    void send_regist(QString,QString);

private slots:
    void draw_warning(QString);
    void on_login_button_clicked();
    void on_register_button_clicked();
    void on_exit_button_clicked();
    void on_submit_login_clicked();
    void on_submit_register_clicked();
    void on_back_button_clicked();
    void on_user_password_returnPressed();
    void on_confirm_password_returnPressed();
};

#endif // LOGIN_WIDGET_H
