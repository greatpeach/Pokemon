#include "my_pokemon.h"

double counter_talbe[6][6] = { 1, 1,  1,  1,  1,  1,
                               2, 2,  2,  2,  2,  2,
                               1, 1,  1,  1,  2,  1,
                               1, 1,  1,  1, 0.5, 2,
                               1, 1, 0.5, 2,  1, 0.5,
                               1, 1,  1, 0.5, 2,  1 };

const double p_critical = 0.1;
const double p_evade = 0.1;
const double p_paralyze = 0.1;
const double p_burn = 0.1;
const double p_drown_1 = 0.1;
const double p_drown_2 = 0.2;


bullet::bullet()
{
    this->element = NORMAL;
    this->element = NORMAL;
    this->total_damage = 0;
}

bullet::bullet(const bullet &sample)
{
    this->element = sample.element;
    this->element_damage = sample.element_damage;
    this->total_damage = sample.total_damage;
}

void bullet::operator=(const bullet &sample)
{
    this->element = sample.element;
    this->element_damage = sample.element_damage;
    this->total_damage = sample.total_damage;
}



my_pokemon::my_pokemon()
{
    this->level = 1;
    this->exp = 0;
    this->status = NORMAL;
    this->remaining_chaos_time = 0;
}

void my_pokemon::level_up_for_all()
{
    this->level++;
    this->remaining_hp = this->total_hp;
    this->remaining_pp = this->total_pp;
    this->power = this->total_power;
    this->defence = this->total_defence;
    this->status = NORMAL;
    this->remaining_chaos_time = 0;
}

void my_pokemon::if_level_up()
{
    if (this->level < 15)
        if (level*level*level <= this->exp)
        {
            emit lv_up(this->level);
            level_up();
        }
}

bullet* my_pokemon::attack()//普通攻击
{
    bullet *bul = new bullet;
    bul->element = NORMAL;
    bul->element_damage = NORMAL;
    bul->total_damage = ((this->level * 3 + 3)*this->power + 10) * 3 / 2;

    //普通攻击有概率暴击
    if (random_num_generator(p_critical))
    {
        bul->element = CRITICAL;
    }
    QString log;
    log = "%1 使出了普通攻击\n";
    emit insert_log(log.arg(this->name));
    return bul;
}

bool my_pokemon::hit(bullet *bul)
{
    int hurt;
    QString log;
    //触发闪避
    if (random_num_generator(p_evade))
    {
        log = "%1 闪避了\n";
        emit insert_log(log.arg(this->name));
        hurt = 0;
        return false;
    }

    hurt = (bul->total_damage / this->defence)*counter_talbe[bul->element][this->element];
    QString debug = "hurt=(%1 // %2)*%3";
    if (bul->element == CRITICAL)
    {
        log = "会心一击，%1 受到了 %2 伤害\n";
        emit insert_log(log.arg(this->name).arg(hurt));
    }
    else if(counter_talbe[bul->element][this->element]==2)
    {
        log = "效果拔群，%1 受到了 %2 伤害\n";
        emit insert_log(log.arg(this->name).arg(hurt));
    }
    else if(counter_talbe[bul->element][this->element]==0.5)
    {
        log = "效果不理想，%1 受到了 %2 伤害\n";
        emit insert_log(log.arg(this->name).arg(hurt));
    }
    else
    {
        log = "%1 受到了 %2 伤害\n";
        emit insert_log(log.arg(this->name).arg(hurt));
    }

    if(bul->element_damage!=NORMAL&&bul->element_damage!=CRITICAL)
    {
        switch (bul->element_damage)
        {
        case FIRE:
            log = "%1 灼伤了\n";
            emit insert_log(log.arg(this->name));
            break;

        case WATER:
            log = "%1 溺水了\n";
            emit insert_log(log.arg(this->name));
            break;

        case ELECTRICITY:
            log = "%1 麻痹了\n";
            emit insert_log(log.arg(this->name));
            break;
        }
        this->remaining_chaos_time = 3;
        this->status = bul->element_damage;
    }

    if (hurt >= this->remaining_hp)
    {
        this->remaining_hp = 0;
        return true;//表示血量为0，失败
    }
    else
    {
        this->remaining_hp -= hurt;
        return false;
    }
}

void my_pokemon::hp_recover(double rate)
{
    QString log;
    int recover = rate*total_hp;
    if (recover + remaining_hp >= total_hp)
    {
        remaining_hp = total_hp;
        log = "%1 的血量回满了\n";
        emit insert_log(log.arg(this->name));
    }
    else
    {
        remaining_hp += recover;
        log = "%1 的血量回复了 %2\n";
        emit insert_log(log.arg(this->name).arg(recover));
    }
}

void my_pokemon::debuff_recover()
{
    status = NORMAL;
    remaining_chaos_time = 0;
    power = total_power;
    defence = total_defence;
}

void my_pokemon::recover()
{
    debuff_recover();
    this->remaining_hp = this->total_hp;
    this->remaining_pp = this->total_pp;
}

my_pkm_container my_pokemon::to_pkmcontainer()
{
    my_pkm_container temp(num, id, name, level, exp, total_hp, total_power, total_defence, attack_interval);
    temp.remaining_hp = remaining_hp;
    temp.power = power;
    temp.defence = defence;
    temp.status = status;
    temp.remaining_chaos_time = remaining_chaos_time;
    temp.total_pp = total_pp;
    temp.remaining_pp = remaining_pp;
    QString skill_name;
    return temp;
}

//若精灵血量归0，则返回1
int my_pokemon::deal_with_debuff()
{
    //异常状态的恢复
    QString log;
    if (this->status == NORMAL)
        return false;
    if (remaining_chaos_time == 0 && this->status!=NORMAL)
    {
        if (this->status == WATER)
        {
            this->power = this->total_power;
            this->defence = this->total_defence;
        }
        this->status = NORMAL;
        log = "%1 的异常状态恢复了";
        emit insert_log(log.arg(this->name));
        return false;
    }
    int debuff;
    int debuff_power;
    int debuff_defence;
    switch (this->status)
    {
    case ELECTRICITY:
        log = "%1 受到麻痹异常状态影响，无法行动，异常状态还有 %2 回合\n";
        emit insert_log(log.arg(this->name).arg(this->remaining_chaos_time));
        break;

    case FIRE:
        debuff = 0.05*total_hp + 1;
        log = "%1 受到灼伤异常状态影响，血量持续减少 ，异常状态还有 %2 回合\n";
        emit insert_log(log.arg(this->name).arg(this->remaining_chaos_time));
        if (remaining_hp > debuff)
        {
            remaining_hp -= debuff;
            log = "血量减少 %1";
            emit insert_log(log.arg(debuff));
        }
        else
        {
            remaining_hp = 0;
            log = "血量减少为0";
            emit insert_log(log);
            return true;
        }
        break;

    case WATER:
        log = "%1 受到溺水异常状态影响，攻击力防御力降低，异常状态还有 %2 回合\n";
        emit insert_log(log);
        debuff_power = power*0.2;
        debuff_defence = defence*0.2;
        if (remaining_chaos_time == 3)
        {
            this->power -= debuff_power;
            this->defence -= debuff_defence;
            log = "攻击力降低 %1，防御力降低 %2\n";
            insert_log(log.arg(debuff_power).arg(debuff_defence));
        }
        break;
    }
    this->remaining_chaos_time--;
    return false;
}

void my_pokemon::get_exp(int exp)
{
    this->exp += exp;
    if_level_up();
}




//主类
//敏捷型
my_Speed::my_Speed()
{
    this->attribute = SPEED;
    this->total_hp = 300;
    this->remaining_hp = this->total_hp;
    this->total_power = 30;
    this->total_defence = 30;
    this->power = this->total_power;
    this->defence = this->total_defence;
    this->attack_interval = 400;
}

void my_Speed::level_up()
{
    this->total_power += (3 * (1 + random_num_generator(0.1)));
    this->total_defence += (3 * (1 + random_num_generator(0.1)));
    this->attack_interval -= (5 * (1 + random_num_generator(0.1)));
    this->total_hp += (10 * (1 + random_num_generator(0.1)));
    this->level_up_for_all();
    if_level_up();
}

//力量型
my_Attack::my_Attack()
{
    this->attribute = ATTACK;
    this->total_hp = 300;
    this->remaining_hp = this->total_hp;
    this->total_power = 40;
    this->total_defence = 30;
    this->power = this->total_power;
    this->defence = this->total_defence;
    this->attack_interval = 500;
}

void my_Attack::level_up()
{
    this->total_power += (5 * (1 + random_num_generator(0.1)));
    this->total_defence += (3 * (1 + random_num_generator(0.1)));
    this->attack_interval -= (2 * (1 + random_num_generator(0.1)));
    this->total_hp += (10 * (1 + random_num_generator(0.1)));
    this->level_up_for_all();
    if_level_up();
}

//防御型
my_Defence::my_Defence()
{
    this->attribute = DEFENCE;
    this->total_hp = 300;
    this->remaining_hp = this->total_hp;
    this->total_power = 30;
    this->total_defence = 40;
    this->power = this->total_power;
    this->defence = this->total_defence;
    this->attack_interval = 500;
}

void my_Defence::level_up()
{
    this->total_power += (3 * (1 + random_num_generator(0.1)));
    this->total_defence += (5 * (1 + random_num_generator(0.1)));
    this->attack_interval -= (2 * (1 + random_num_generator(0.1)));
    this->total_hp += (10 * (1 + random_num_generator(0.1)));
    this->level_up_for_all();
    if_level_up();
};

//肉盾型
my_Tank::my_Tank()
{
    this->attribute = TANK;
    this->total_hp = 350;
    this->remaining_hp = this->total_hp;
    this->total_power = 30;
    this->total_defence = 30;
    this->power = this->total_power;
    this->defence = this->total_defence;
    this->attack_interval = 500;
}

void my_Tank::level_up()
{
    this->total_power += (3 * (1 + random_num_generator(0.1)));
    this->total_defence += (3 * (1 + random_num_generator(0.1)));
    this->attack_interval -= (2 * (1 + random_num_generator(0.1)));
    this->total_hp += (20 * (1 + random_num_generator(0.1)));
    this->level_up_for_all();
    if_level_up();
}



//皮卡丘
my_Pikachu::my_Pikachu(int level)
{
    this->id = 1;
    this->name = "Pikachu";
    this->element = ELECTRICITY;
    this->total_pp = 15;
    this->remaining_pp = this->total_pp;
    this->skill_name = "十万伏特";

    this->exp = (level - 1)*(level - 1)*(level - 1);
    if_level_up();
}

my_Pikachu::my_Pikachu(int num, int id, QString name, int level, int exp, int hp, int power, int defence, int attack_interval)
{
    this->num = num;
    this->id = id;
    this->name = name;
    this->level = level;
    this->exp = exp;
    this->total_hp = hp;
    this->total_power = power;
    this->total_defence = defence;
    this->attack_interval = attack_interval;

    this->power = this->total_power;
    this->defence = this->total_defence;
    this->remaining_hp = this->total_hp;
    this->status = NORMAL;
    this->remaining_chaos_time = 0;


    this->attribute = SPEED;
    this->element = ELECTRICITY;
    this->total_pp = 15;
    this->remaining_pp = this->total_pp;
    this->skill_name = "十万伏特";
}

bullet* my_Pikachu::skill()
{
    QString log;
    log = "%1 使用了 %2 ";
    emit insert_log(log.arg(this->name).arg(this->skill_name));

    this->remaining_pp--;
    bullet *bul = new bullet;
    bul->element = this->element;
    bul->total_damage = (this->level * 3.5 + 2)*this->power + 2;
    bul->total_damage *= 1.5;
    if (random_num_generator(p_paralyze))
        bul->element_damage = this->element;
    else
        bul->element_damage = NORMAL;
    return bul;

}

//小火龙
my_Hitokage::my_Hitokage(int level)
{
    this->id = 2;
    this->name = "Hitokage";
    this->element = FIRE;
    this->total_pp = 5;
    this->remaining_pp = this->total_pp;
    this->skill_name = "大火球";

    this->exp = (level - 1)*(level - 1)*(level - 1);
    if_level_up();
}

my_Hitokage::my_Hitokage(int num, int id, QString name, int level, int exp, int hp, int power, int defence, int attack_interval)
{
    this->num = num;
    this->id = id;
    this->name = name;
    this->level = level;
    this->exp = exp;
    this->total_hp = hp;
    this->total_power = power;
    this->total_defence = defence;
    this->attack_interval = attack_interval;

    this->power = this->total_power;
    this->defence = this->total_defence;
    this->remaining_hp = this->total_hp;
    this->status = NORMAL;
    this->remaining_chaos_time = 0;


    this->attribute = ATTACK;
    this->element = FIRE;
    this->total_pp = 5;
    this->remaining_pp = this->total_pp;
    this->skill_name = "大火球";
}

bullet* my_Hitokage::skill()
{
    QString log;
    log = "%1 使用了 %2 ";
    emit insert_log(log.arg(this->name).arg(this->skill_name));

    this->remaining_pp--;
    bullet *bul = new bullet;
    bul->element = this->element;
    bul->total_damage = (this->level * 3.5)*this->power * 3 / 2 + 2;
    bul->total_damage *= 1.5;
    if (random_num_generator(p_burn))
        bul->element_damage = this->element;
    else
        bul->element_damage = NORMAL;
    return bul;
}

//杰尼龟
my_Zenigame::my_Zenigame(int level)
{
    this->id = 3;
    this->name = "Zenigame";
    this->element = WATER;
    this->total_pp = 5;
    this->remaining_pp = this->total_pp;
    this->skill_name = "水枪";

    this->exp = (level - 1)*(level - 1)*(level - 1);
    if_level_up();
}

my_Zenigame::my_Zenigame(int num, int id, QString name, int level, int exp, int hp, int power, int defence, int attack_interval)
{
    this->num = num;
    this->id = id;
    this->name = name;
    this->level = level;
    this->exp = exp;
    this->total_hp = hp;
    this->total_power = power;
    this->total_defence = defence;
    this->attack_interval = attack_interval;

    this->power = this->total_power;
    this->defence = this->total_defence;
    this->remaining_hp = this->total_hp;
    this->status = NORMAL;
    this->remaining_chaos_time = 0;


    this->attribute = ATTACK;
    this->element = WATER;
    this->total_pp = 5;
    this->remaining_pp = this->total_pp;
    this->skill_name = "水枪";
}

bullet* my_Zenigame::skill()
{

    QString log;
    log = "%1 使用了 %2 ";
    emit insert_log(log.arg(this->name).arg(this->skill_name));
    this->remaining_pp--;
    bullet *bul = new bullet;
    bul->element = this->element;
    bul->total_damage = (this->level * 3.5 + 2)*this->power + 2;
    bul->total_damage *= 1.5;
    if (random_num_generator(p_drown_2))
        bul->element_damage = this->element;
    else
        bul->element_damage = NORMAL;
    return bul;
}

//妙蛙种子
my_Fushigidane::my_Fushigidane(int level)
{
    this->id = 4;
    this->name = "Fushigidane";
    this->element = GRASS;
    this->total_pp = 5;
    this->remaining_pp = this->total_pp;
    this->skill_name = "吸收";

    this->exp = (level - 1)*(level - 1)*(level - 1);
    if_level_up();
}

my_Fushigidane::my_Fushigidane(int num, int id, QString name, int level, int exp, int hp, int power, int defence, int attack_interval)
{
    this->num = num;
    this->id = id;
    this->name = name;
    this->level = level;
    this->exp = exp;
    this->total_hp = hp;
    this->total_power = power;
    this->total_defence = defence;
    this->attack_interval = attack_interval;

    this->power = this->total_power;
    this->defence = this->total_defence;
    this->remaining_hp = this->total_hp;
    this->status = NORMAL;
    this->remaining_chaos_time = 0;


    this->attribute = TANK;
    this->element = GRASS;
    this->total_pp = 5;
    this->remaining_pp = this->total_pp;
    this->skill_name = "吸收";
}

bullet* my_Fushigidane::skill()
{
    QString log;
    log = "%1 使用了 %2 ";
    emit insert_log(log.arg(this->name).arg(this->skill_name));

    this->remaining_pp--;
    bullet *bul = new bullet;
    bul->element = this->element;
    bul->total_damage = (this->level * 3.5 - 1)*this->power + 2;
    bul->total_damage *= 1.5;
    bul->element_damage = NORMAL;
    if (this->remaining_hp < this->total_hp*0.9)
    {
        log = "血量恢复了 %1 \n";
        emit insert_log(log.arg(this->total_hp*0.1));
        this->remaining_hp += 0.1*this->total_hp;
    }
    else
    {
        this->remaining_hp = this->total_hp;
        log = "血量回满了 \n";
        emit insert_log(log);
    }
    return bul;
}

//白海狮
my_Dewgong::my_Dewgong(int level)
{
    this->id = 5;
    this->name = "Dewgong";
    this->element = WATER;
    this->total_pp = 15;
    this->remaining_pp = this->total_pp;
    this->skill_name = "冲浪术";

    this->exp = (level - 1)*(level - 1)*(level - 1);
    if_level_up();
}

my_Dewgong::my_Dewgong(int num, int id, QString name, int level, int exp, int hp, int power, int defence, int attack_interval)
{
    this->num = num;
    this->id = id;
    this->name = name;
    this->level = level;
    this->exp = exp;
    this->total_hp = hp;
    this->total_power = power;
    this->total_defence = defence;
    this->attack_interval = attack_interval;

    this->power = this->total_power;
    this->defence = this->total_defence;
    this->remaining_hp = this->total_hp;
    this->status = NORMAL;
    this->remaining_chaos_time = 0;


    this->attribute = TANK;
    this->element = WATER;
    this->total_pp = 15;
    this->remaining_pp = this->total_pp;
    this->skill_name = "冲浪术";
}

bullet* my_Dewgong::skill()
{
    QString log;
    log = "%1 使用了 %2 ";
    emit insert_log(log.arg(this->name).arg(this->skill_name));

    this->remaining_pp--;
    bullet *bul = new bullet;
    bul->element = this->element;
    bul->total_damage = (this->level * 3.5 + 2)*this->power + 2;
    bul->total_damage *= 1.5;
    if (random_num_generator(p_drown_1))
        bul->element_damage = this->element;
    else
        bul->element_damage = NORMAL;
    return bul;
}

//大舌头
my_Peroringa::my_Peroringa(int level)
{
    this->id = 5;
    this->name = "Peroringa";
    this->element = NORMAL;
    this->total_pp = 15;
    this->remaining_pp = this->total_pp;
    this->skill_name = "舔";

    this->exp = (level - 1)*(level - 1)*(level - 1);
    if_level_up();
}

my_Peroringa::my_Peroringa(int num, int id, QString name, int level, int exp, int hp, int power, int defence, int attack_interval)
{
    this->num = num;
    this->id = id;
    this->name = name;
    this->level = level;
    this->exp = exp;
    this->total_hp = hp;
    this->total_power = power;
    this->total_defence = defence;
    this->attack_interval = attack_interval;

    this->power = this->total_power;
    this->defence = this->total_defence;
    this->remaining_hp = this->total_hp;
    this->status = NORMAL;
    this->remaining_chaos_time = 0;


    this->attribute = DEFENCE;
    this->element = NORMAL;
    this->total_pp = 15;
    this->remaining_pp = this->total_pp;
    this->skill_name = "舔";
}

bullet* my_Peroringa::skill()
{
    QString log;
    log = "%1 使用了 %2 ";
    emit insert_log(log.arg(this->name).arg(this->skill_name));
    this->remaining_pp--;
    bullet *bul = new bullet;
    bul->element = this->element;
    bul->total_damage = (this->level * 3.5 + 2)*this->power + 2;
    bul->total_damage *= 1.5;
    if (random_num_generator(0.1))
        bul->element_damage = this->element;
    else
        bul->element_damage = NORMAL;
    return bul;
}

//生成随机数
int random_num_generator(double p)//p为事件发生概率
{
    int random = rand()%100;
    if (random < p * 100)
        return 1;
    else
        return 0;
}

my_pkm_container::my_pkm_container(int num, int id, QString name, int level, int exp, int hp, int power, int defence, int attack_interval)
{
    this->num = num;
    this->id = id;
    this->name = name;
    this->level = level;
    this->exp = exp;
    this->total_hp = hp;
    this->total_power = power;
    this->total_defence = defence;
    this->attack_interval = attack_interval;

    this->power = this->total_power;
    this->defence = this->total_defence;
    this->remaining_hp = this->total_hp;
    this->status = NORMAL;
    this->remaining_chaos_time = 0;

    switch(id)
    {
    case PIKACHU:
        this->attribute = SPEED;
        this->element = ELECTRICITY;
        this->total_pp = 15;
        this->remaining_pp = this->total_pp;
        this->skill_name = "十万伏特";
        break;

    case HITOKAGE:
        this->attribute = ATTACK;
        this->element = FIRE;
        this->total_pp = 5;
        this->remaining_pp = this->total_pp;
        this->skill_name = "大火球";
        break;

    case ZENIGAME:
        this->attribute = ATTACK;
        this->element = WATER;
        this->total_pp = 5;
        this->remaining_pp = this->total_pp;
        this->skill_name = "水枪";
        break;

    case FUSHIGIDANE:
        this->attribute = TANK;
        this->element = GRASS;
        this->total_pp = 5;
        this->remaining_pp = this->total_pp;
        this->skill_name = "吸收";
        break;

    case DEWGONG:
        this->attribute = TANK;
        this->element = WATER;
        this->total_pp = 15;
        this->remaining_pp = this->total_pp;
        this->skill_name = "冲浪术";
        break;

    case PERORINGA:
        this->attribute = DEFENCE;
        this->element = NORMAL;
        this->total_pp = 15;
        this->remaining_pp = this->total_pp;
        this->skill_name = "舔";
        break;
    }

}

my_pkm_container::my_pkm_container(const my_pkm_container &sample)
{
    num = sample.num;
    id = sample.id;
    name = sample.name;
    attribute = sample.attribute;
    element = sample.element;
    level = sample.level;
    exp = sample.exp;

    total_hp = sample.total_hp;
    remaining_hp = sample.remaining_hp;
    power = sample.power;//攻击力
    defence = sample.defence;//防御力
    attack_interval = sample.attack_interval;//攻击间隔
    status = sample.status;//精灵状态（是否属性异常）
    remaining_chaos_time = sample.remaining_chaos_time;//状态异常剩余时间
    total_pp = sample.total_pp;//技能使用次数
    remaining_pp = sample.remaining_pp;//剩余技能使用次数
    total_power = sample.total_power;//用于恢复到原攻击力
    total_defence = sample.total_defence;//用于恢复到原防御力
    skill_name = sample.skill_name;//技能名称
}

my_pkm_container my_pkm_container::operator=(const my_pkm_container &sample)
{
    num = sample.num;
    id = sample.id;
    name = sample.name;
    attribute = sample.attribute;
    element = sample.element;
    level = sample.level;
    exp = sample.exp;

    total_hp = sample.total_hp;
    remaining_hp = sample.remaining_hp;
    power = sample.power;//攻击力
    defence = sample.defence;//防御力
    attack_interval = sample.attack_interval;//攻击间隔
    status = sample.status;//精灵状态（是否属性异常）
    remaining_chaos_time = sample.remaining_chaos_time;//状态异常剩余时间
    total_pp = sample.total_pp;//技能使用次数
    remaining_pp = sample.remaining_pp;//剩余技能使用次数
    total_power = sample.total_power;//用于恢复到原攻击力
    total_defence = sample.total_defence;//用于恢复到原防御力
    skill_name = sample.skill_name;//技能名称
    return *this;
}

QByteArray my_pkm_container::toByteArray()
{
    QByteArray msg;
    msg = QByteArray::number(num);
    msg += ";" + QByteArray::number(id);
    msg += ";" + name;
    msg += ";" + QByteArray::number(level);
    msg += ";" + QByteArray::number(exp);
    msg += ";" + QByteArray::number(total_hp);
    msg += ";" + QByteArray::number(total_power);
    msg += ";" + QByteArray::number(total_defence);
    msg += ";" + QByteArray::number(attack_interval);
    return msg;
}

void my_pkm_container::print()
{
    qDebug() << num;//精灵的唯一标识
    qDebug() << id;//精灵种类
    qDebug() << name;
    qDebug() << attribute;//精灵类别
    qDebug() << element;//精灵属性
    qDebug() << level;
    qDebug() << exp;

    qDebug() << total_hp;
    qDebug() << remaining_hp;
    qDebug() << power;//攻击力
    qDebug() << defence;//防御力
    qDebug() << attack_interval;//攻击间隔
    qDebug() << status;//精灵状态（是否属性异常）
    qDebug() << remaining_chaos_time;//状态异常剩余时间
    qDebug() << total_pp;//技能使用次数
    qDebug() << remaining_pp;//剩余技能使用次数
    qDebug() << total_power;//用于恢复到原攻击力
    qDebug() << total_defence;//用于恢复到原防御力
    qDebug() << skill_name;//技能名称
}
