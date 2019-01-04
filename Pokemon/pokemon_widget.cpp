#include "pokemon_widget.h"
#include "ui_pokemon_widget.h"

pokemon_widget::pokemon_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pokemon_widget)
{
    ui->setupUi(this);
}

pokemon_widget::~pokemon_widget()
{
    delete ui;
}

//显示别人的精灵
void pokemon_widget::show_pokemon(my_pkm_container pkm)
{
    this->pkm = pkm;
    ui->name->setText(pkm.name);
    ui->level->setText(QString::number(pkm.level));
    ui->exp->setText(QString::number(pkm.exp)+"/"+QString::number(pkm.level*pkm.level*pkm.level));
    ui->hp->setText(QString::number(pkm.total_hp));
    ui->power->setText(QString::number(pkm.total_power));
    ui->defence->setText(QString::number(pkm.defence));
    ui->attack_interval->setText(QString::number(pkm.attack_interval));
    ui->skill_name->setText(pkm.skill_name);
    ui->pp->setText(QString::number(pkm.total_pp));
    switch(pkm.id)
    {
    case PIKACHU:
        ui->pic->setStyleSheet("border-image: url(:/Pikachu.png);");
        ui->attribute->setText(QString::fromUtf8("速度型"));
        ui->element->setText(QString::fromUtf8("电"));
        ui->skill_effect->setText("电属性技能，有10%概率使对方麻痹");
        break;

    case HITOKAGE:
        ui->pic->setStyleSheet("border-image: url(:/Hitokage.png);");
        ui->attribute->setText(QString::fromUtf8("攻击型"));
        ui->element->setText(QString::fromUtf8("火"));
        ui->skill_effect->setText("火属性技能，有10%概率使对方灼伤");
        break;

    case ZENIGAME:
        ui->pic->setStyleSheet("border-image: url(:/Zenigame.png);");
        ui->attribute->setText(QString::fromUtf8("攻击型"));
        ui->element->setText(QString::fromUtf8("水"));
        ui->skill_effect->setText("水属性技能，有20%概率使对方溺水");
        break;

    case FUSHIGIDANE:
        ui->pic->setStyleSheet("border-image: url(:/Fushigidane.png);");
        ui->attribute->setText(QString::fromUtf8("坦克型"));
        ui->element->setText(QString::fromUtf8("草"));
        ui->skill_effect->setText("草属性技能，恢复自身生命值");
        break;

    case DEWGONG:
        ui->pic->setStyleSheet("border-image: url(:/Dewgong.png);");
        ui->attribute->setText(QString::fromUtf8("坦克型"));
        ui->element->setText(QString::fromUtf8("水"));
        ui->skill_effect->setText("水属性技能，有10%概率使对方麻痹");
        break;

    case PERORINGA:
        ui->pic->setStyleSheet("border-image: url(:/Peroringa.png);");
        ui->attribute->setText(QString::fromUtf8("防御型"));
        ui->element->setText(QString::fromUtf8("普通"));
        ui->skill_effect->setText("普通系技能");
        break;

    }
}

//显示自己的精灵
void pokemon_widget::show_own_pokemon(my_pkm_container pkm)
{
    this->pkm = pkm;
    ui->name->setText(pkm.name);
    ui->name->setReadOnly(false);
    ui->level->setText(QString::number(pkm.level));
    ui->exp->setText(QString::number(pkm.exp)+"/"+QString::number(pkm.level*pkm.level*pkm.level));
    ui->hp->setText(QString::number(pkm.remaining_hp)+"/"+QString::number(pkm.total_hp));
    ui->power->setText(QString::number(pkm.power)+"/"+QString::number(pkm.total_power));
    ui->defence->setText(QString::number(pkm.defence)+"/"+QString::number(pkm.defence));
    ui->attack_interval->setText(QString::number(pkm.attack_interval));
    ui->skill_name->setText(pkm.skill_name);
    ui->pp->setText(QString::number(pkm.remaining_pp)+"/"+QString::number(pkm.total_pp));
    switch(pkm.id)
    {
    case PIKACHU:
        ui->pic->setStyleSheet("border-image: url(:/Pikachu.png);");
        ui->attribute->setText(QString::fromUtf8("速度型"));
        ui->element->setText(QString::fromUtf8("电"));
        ui->skill_effect->setText("电属性技能，有10%概率使对方麻痹");
        break;

    case HITOKAGE:
        ui->pic->setStyleSheet("border-image: url(:/Hitokage.png);");
        ui->attribute->setText(QString::fromUtf8("攻击型"));
        ui->element->setText(QString::fromUtf8("火"));
        ui->skill_effect->setText("火属性技能，有10%概率使对方灼伤");
        break;

    case ZENIGAME:
        ui->pic->setStyleSheet("border-image: url(:/Zenigame.png);");
        ui->attribute->setText(QString::fromUtf8("攻击型"));
        ui->element->setText(QString::fromUtf8("水"));
        ui->skill_effect->setText("水属性技能，有20%概率使对方溺水");
        break;

    case FUSHIGIDANE:
        ui->pic->setStyleSheet("border-image: url(:/Fushigidane.png);");
        ui->attribute->setText(QString::fromUtf8("坦克型"));
        ui->element->setText(QString::fromUtf8("草"));
        ui->skill_effect->setText("草属性技能，恢复自身生命值");
        break;

    case DEWGONG:
        ui->pic->setStyleSheet("border-image: url(:/Dewgong.png);");
        ui->attribute->setText(QString::fromUtf8("坦克型"));
        ui->element->setText(QString::fromUtf8("水"));
        ui->skill_effect->setText("水属性技能，有10%概率使对方溺水");
        break;

    case PERORINGA:
        ui->pic->setStyleSheet("border-image: url(:/Peroringa.png);");
        ui->attribute->setText(QString::fromUtf8("防御型"));
        ui->element->setText(QString::fromUtf8("普通"));
        ui->skill_effect->setText("普通系技能");
        break;
    }
    this->show();
}

//更新精灵名字
void pokemon_widget::on_name_returnPressed()
{
    this->pkm.name = ui->name->text();
    emit pkm_changed(pkm);
}
